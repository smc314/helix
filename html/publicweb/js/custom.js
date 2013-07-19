function hideAllBenefits() {
	document.getElementById("Benefit1").style.display = 'none';
	document.getElementById("Benefit1_link").className = 'none';
	document.getElementById("Benefit2").style.display = 'none';
	document.getElementById("Benefit2_link").className = 'none';
	document.getElementById("Benefit3").style.display = 'none';
	document.getElementById("Benefit3_link").className = 'none';
	document.getElementById("Benefit4").style.display = 'none';
	document.getElementById("Benefit4_link").className = 'none';
	document.getElementById("Benefit5").style.display = 'none';
	document.getElementById("Benefit5_link").className = 'none';
	document.getElementById("Benefit6").style.display = 'none';
	document.getElementById("Benefit6_link").className = 'none';
	document.getElementById("Benefit7").style.display = 'none';
	document.getElementById("Benefit7_link").className = 'none';
	document.getElementById("Benefit8").style.display = 'none';
	document.getElementById("Benefit8_link").className = 'last';
}
function showBenefit(theID) {
	hideAllBenefits();
	document.getElementById(theID).style.display = 'block';
	if(theID === "Benefit8"){
		document.getElementById(theID + "_link").className = 'last current';
	} else {
		document.getElementById(theID + "_link").className = 'current';
	}
}

function hideAllProducts() {
	document.getElementById("Build_Web").style.display = 'none';
	document.getElementById("Build_Web_link").className = 'none';
	document.getElementById("Code_Generation").style.display = 'none';
	document.getElementById("Code_Generation_link").className = 'none';
	document.getElementById("Deployment_Platforms").style.display = 'none';
	document.getElementById("Deployment_Platforms_link").className = 'none';
	document.getElementById("Open_Source").style.display = 'none';
	document.getElementById("Open_Source_link").className = 'none';
}
function showProduct(theID){
	hideAllProducts();
	document.getElementById(theID).style.display = 'block';
	document.getElementById(theID + "_link").className = 'current';
}

function verifyTrialForm() {
	if (document.trialinput.contactname.value === "") {
		alert("Please provide a Contact Name");
		document.trialinput.contactname.focus();
		return false;
	}
	if (document.trialinput.contactemail.value === "") {
		alert("Please provide a Contact EMail Address");
		document.trialinput.contactemail.focus();
		return false;
	}
	// if we get through all of that, we're good to submit.
	document.trialinput.submit();
}

function askSupportQuestion() {
	if (document.questioninput.contactname.value === "") {
		alert("Please provide your Name");
		document.questioninput.contactname.focus();
		return false;
	}
	if (document.questioninput.contactemail.value === "") {
		alert("Please provide an EMail Address");
		document.questioninput.contactemail.focus();
		return false;
	}
	if (document.questioninput.questioncontent.value === "") {
		alert("Please type in your Question");
		document.questioninput.questioncontent.focus();
		return false;
	}
	// if we get through all of that, we're good to submit.
	document.questioninput.submit();
}

function verifyCommunityForm() {
	if (document.communityeditioninput.contactname.value === "") {
		alert("Please provide a Contact Name");
		document.communityeditioninput.contactname.focus();
		return false;
	}
	if (document.communityeditioninput.contactemail.value === "") {
		alert("Please provide a Contact EMail Address");
		document.communityeditioninput.contactemail.focus();
		return false;
	}
	// if we get through all of that, we're good to submit.
	document.communityeditioninput.submit();
}

function verifyPurchaseForm() {
	if (document.purchaseinput.newserverqty.value === "") {
		alert("Please provide a Server License Quantity");
		document.purchaseinput.newserverqty.focus();
		return false;
	}
	// if we get through all of that, we're good to submit.
	document.purchaseinput.submit();
}


var hericus = {};
hericus.newwindow = '';
hericus.displayScreenShot = function(url) {
	try {
		if (hericus.newwindow.location && !hericus.newwindow.closed) {
			hericus.newwindow.close();
		}
	} catch (exception){
		
	}
	var width = 1120;
	var height = 840;
	var options = 'width=' + width + ",height=" + height + ",resizeable=1,left=100,top=100";
	hericus.newwindow=window.open(url,'htmlname',options);
}
