<?php

include ('db.php');

$id=$_GET['eid'];
if($id=="")
{
echo '<script>alert("Sorry ! Wrong Entry") </script>' ;
		header("Location: sendletter.php");


}

else{
$view="DELETE FROM `contact` WHERE id ='$id' ";

	if($re = mysqli_query($con,$view))
	{
		echo '<script>alert("News Letter Subscriber Remove") </script>' ;
		header("Location: sendletter.php");
	}


}







?>