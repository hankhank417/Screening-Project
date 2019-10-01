<?php
	include ('db.php');
	$id = $_GET['bid'];
	if($id!="") {
		$view = "DELETE FROM `cart` WHERE bId = $id";
		mysqli_query($con,$view);
		$sql = "UPDATE `cart` SET bId = bId-1 Where bId > $id";
		mysqli_query($con,$sql);
	}
	header("Location: cart.php");
?>