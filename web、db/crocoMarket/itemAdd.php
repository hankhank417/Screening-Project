<?php
	include ('db.php');
	$id = $_GET['bid'];
	if($id=="") {
		echo '<script>alert("Sorry ! Wrong Entry") </script>' ;
		header("Location: cart.php");
	}else{
		$view = "UPDATE `Cart` SET `quantity` = (`quantity`+1) WHERE bId = '$id' ";
		mysqli_query($con,$view);
		header("Location: cart.php");
	}
?>