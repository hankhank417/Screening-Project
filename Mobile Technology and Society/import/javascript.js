var slideIndex = 1;
showDivs(slideIndex);
function plusDivs(n) {
  showDivs(slideIndex += n);
}
function showDivs(n) {
  var i;
  var x = document.getElementsByClassName("mySlides");
  if (n > x.length) {slideIndex = 1}    
  if (n < 1) {slideIndex = x.length}
  for (i = 0; i < x.length; i++) {
     x[i].style.display = "none";  
  }
  x[slideIndex-1].style.display = "block";
}

document.getElementById('submit').addEventListener('click',cleanData);
function cleanData(){
	if ( document.getElementById('student_name').value != "" && document.getElementById('ID').value != "" ) {
		alert('Already applied');
	}else{
		if( document.getElementById('student_name').value == "" && document.getElementById('ID').value == "")
			alert('Form is empty');
		else if( document.getElementById('student_name').value == "" )
			alert('Name is empty');
		else
			alert('ID is empty');

	}
	document.getElementById('student_name').value = "";
	document.getElementById('ID').value = "";
}

document.getElementById('search_area_img').addEventListener('click',cleanSearch);
function cleanSearch(){
	document.getElementById('search_input').value = "";
}

function openNav() {
    document.getElementById("mySidenav").style.width = "200px";
    document.getElementById("main").style.marginLeft = "200px";
}

function closeNav() {
    document.getElementById("mySidenav").style.width = "0";
    document.getElementById("main").style.marginLeft= "0";
}