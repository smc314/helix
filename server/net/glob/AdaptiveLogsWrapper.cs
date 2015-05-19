/* ***************************************************************************
   Copyright (c): 2013 Hericus Software, Inc.
   License: The MIT License (MIT)
   Authors: Steven M. Cherry
*************************************************************************** */
using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using NLog;
using NLog.Common;
using NLog.Config;
using NLog.Targets;
using NLog.Targets.Wrappers;

namespace Helix.Glob
{
    /// <summary>
    /// Implements an adaptive logging wrapper using the NLog infrastructure.
    /// </summary>
    [Target("AdaptiveLogs", IsWrapper = true)]
    public class AdaptiveLogsWrapper : WrapperTargetBase
    {
        [RequiredParameter]
        public int MaxBufferSize { get; set; }

        [RequiredParameter]
        public bool FatalOn { get; set; }
        [RequiredParameter]
        public bool FatalBufferWhenOff { get; set; }
        [RequiredParameter]
        public int FatalDumpWhenHit { get; set; }

        [RequiredParameter]
        public bool ErrorOn { get; set; }
        [RequiredParameter]
        public bool ErrorBufferWhenOff { get; set; }
        [RequiredParameter]
        public int ErrorDumpWhenHit { get; set; }

        [RequiredParameter]
        public bool WarnOn { get; set; }
        [RequiredParameter]
        public bool WarnBufferWhenOff { get; set; }
        [RequiredParameter]
        public int WarnDumpWhenHit { get; set; }

        [RequiredParameter]
        public bool InfoOn { get; set; }
        [RequiredParameter]
        public bool InfoBufferWhenOff { get; set; }
        [RequiredParameter]
        public int InfoDumpWhenHit { get; set; }

        [RequiredParameter]
        public bool DebugOn { get; set; }
        [RequiredParameter]
        public bool DebugBufferWhenOff { get; set; }
        [RequiredParameter]
        public int DebugDumpWhenHit { get; set; }

        [RequiredParameter]
        public bool TraceOn { get; set; }
        [RequiredParameter]
        public bool TraceBufferWhenOff { get; set; }
        [RequiredParameter]
        public int TraceDumpWhenHit { get; set; }

        /// <summary>
        /// This is the queue that we use to collect information from the logging
        /// statements that are scattered throughout the code.  Use this because
        /// we are running on a separate thread.
        /// </summary>
        private BlockingCollection<AsyncLogEventInfo> m_log_queue;

        /// <summary>
        /// Our log buffer of previous messages
        /// </summary>
        private List < AsyncLogEventInfo > m_log_buffer;

        /// <summary>
        /// The thread that handles adaptive logging
        /// </summary>
        private Thread m_adaptive_logs_thread;

        private volatile bool m_shutdown;
        private volatile bool m_paused;

        public AdaptiveLogsWrapper()
        {
            m_log_queue = new BlockingCollection<AsyncLogEventInfo>();
            m_log_buffer = new List<AsyncLogEventInfo>();
            m_shutdown = false;
            m_paused = false;
        }

        public AdaptiveLogsWrapper(Target wrappedTarget)
        {
            m_log_queue = new BlockingCollection<AsyncLogEventInfo>();
            m_log_buffer = new List<AsyncLogEventInfo>();
            m_shutdown = false;
            m_paused = false;
            this.WrappedTarget = wrappedTarget;
        }

        /// <summary>
        /// We override the Write method to simply add the incomming message to our
        /// queue and return.  It will be processed by the AdaptiveLogs thread.
        /// </summary>
        /// <remarks>
        /// The <see cref="Target.PrecalculateVolatileLayouts"/> is called to ensure
        /// that the log event can be processed in another thread.
        /// </remarks>
        /// <param name="logEvent"></param>
        protected override void Write(AsyncLogEventInfo logEvent)
        {
            this.MergeEventProperties(logEvent.LogEvent);
            this.PrecalculateVolatileLayouts(logEvent.LogEvent);
            m_log_queue.Add(logEvent); // Drop it off for processing.
        }

        /// <summary>
        /// Initializes the target by starting the AdaptiveLogging thread
        /// </summary>
        protected override void InitializeTarget()
        {
            base.InitializeTarget();
            m_shutdown = false;
            m_paused = false;
            try
            {
                m_adaptive_logs_thread = new Thread(this.Execute);
                m_adaptive_logs_thread.Name = "AdaptiveLogger";
                m_adaptive_logs_thread.Start();
            }
            catch (Exception e)
            {
                Console.WriteLine("Adaptive Logs: {0}: {1}", e.Message, e.StackTrace);
            }
        }

        protected override void CloseTarget()
        {
            m_paused = true;
            m_shutdown = true;
            DrainLastLogs();
            base.CloseTarget();
        }

        public void Execute()
        {
            try
            {
                while (!m_shutdown)
                {
                    while (!m_paused && !m_shutdown)
                    {
                        AsyncLogEventInfo msg;
                        bool foundItem = m_log_queue.TryTake(out msg, 100);  // Only wait up to 100 ms for a message
                        if (foundItem)
                        {
                            ProcessMessage(msg);
                        }
                    }
                    if (m_paused)
                    {
                        Thread.Sleep(100); // 1/10th second sleep.
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("Adaptive Logs: {0}: {1}", e.Message, e.StackTrace);
            }
        }

        protected void DrainLastLogs()
        {
            // Pull off anything left in the queue - up to 1000 messages
            int count = 0;
            try
            {
                while (count < 1000)
                {
                    AsyncLogEventInfo msg;
                    if (m_log_queue.TryTake(out msg))
                    {
                        ProcessMessage(msg);
                        count++;
                    }
                    else
                    {
                        break; // Nothing left in the queue
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("Adaptive Logs: {0}: {1}", e.Message, e.StackTrace);
            }
        }

        protected void ProcessMessage(AsyncLogEventInfo msg)
        {
            bool isOn = IsChannelOn(msg);
            bool isBuffered = IsChannelBuffered(msg);

            // If it's not on and not buffered, then throw it away:
            if (isOn == false && isBuffered == false)
            {
                return;
            }

            // If it's not on, but buffered, then add it to the buffer
            if (isOn == false && isBuffered == true)
            {
                AddLogToBuffer(msg);
                return;
            }

            // If it's on:
            if (isOn)
            {
                // Tail the buffer by dump_when_hit
                BufferTail(GetDumpCount(msg));

                // Write the log message out
                WriteLogMsg(msg);

                // Empty the buffer, 'cause they're all out of order now
                ClearBuffer();
            }
        }

        protected bool IsChannelOn(AsyncLogEventInfo msg)
        {
            if (msg.LogEvent.Level == LogLevel.Fatal) return FatalOn;
            if (msg.LogEvent.Level == LogLevel.Error) return ErrorOn;
            if (msg.LogEvent.Level == LogLevel.Warn) return WarnOn;
            if (msg.LogEvent.Level == LogLevel.Info) return InfoOn;
            if (msg.LogEvent.Level == LogLevel.Debug) return DebugOn;
            if (msg.LogEvent.Level == LogLevel.Trace) return TraceOn;
            return false; // unknown channel
        }

        protected bool IsChannelBuffered(AsyncLogEventInfo msg)
        {
            if (msg.LogEvent.Level == LogLevel.Fatal) return FatalBufferWhenOff;
            if (msg.LogEvent.Level == LogLevel.Error) return ErrorBufferWhenOff;
            if (msg.LogEvent.Level == LogLevel.Warn) return WarnBufferWhenOff;
            if (msg.LogEvent.Level == LogLevel.Info) return InfoBufferWhenOff;
            if (msg.LogEvent.Level == LogLevel.Debug) return DebugBufferWhenOff;
            if (msg.LogEvent.Level == LogLevel.Trace) return TraceBufferWhenOff;
            return false; // unknown channel
        }

        protected int GetDumpCount(AsyncLogEventInfo msg)
        {
            if (msg.LogEvent.Level == LogLevel.Fatal) return FatalDumpWhenHit;
            if (msg.LogEvent.Level == LogLevel.Error) return ErrorDumpWhenHit;
            if (msg.LogEvent.Level == LogLevel.Warn) return WarnDumpWhenHit;
            if (msg.LogEvent.Level == LogLevel.Info) return InfoDumpWhenHit;
            if (msg.LogEvent.Level == LogLevel.Debug) return DebugDumpWhenHit;
            if (msg.LogEvent.Level == LogLevel.Trace) return TraceDumpWhenHit;
            return 0; // unknown channel
        }

        protected void WriteLogMsg(AsyncLogEventInfo msg)
        {
            this.WrappedTarget.WriteAsyncLogEvent(msg);
            this.WrappedTarget.Flush(msg.Continuation);
        }

        protected void AddLogToBuffer(AsyncLogEventInfo msg)
        {
            m_log_buffer.Add(msg);
            if (m_log_buffer.Count > MaxBufferSize)
            {
                // Delete the message at the front of the buffer.
                m_log_buffer.RemoveAt(0);
            }
        }

        protected void BufferTail(int count)
        {
            int size = m_log_buffer.Count;

            // If they want more than what we have, then just dump the whole thing
            if (count >= size)
            {
                foreach (AsyncLogEventInfo msg in m_log_buffer)
                {
                    this.WrappedTarget.WriteAsyncLogEvent(msg);
                }
                return;
            }

            // If they want less than what we have, then only give 'em the last
            // ones that they asked for
            // 0 1 2 3 4 5 6 7 8 9
            // size = 10
            // count = 6
            // i = 4 == size - count
            for (int i = size - count; i < m_log_buffer.Count; i++)
            {
                this.WrappedTarget.WriteAsyncLogEvent(m_log_buffer[i]);
            }
        }

        protected void ClearBuffer()
        {
            m_log_buffer.Clear();
        }
    
    }
}
