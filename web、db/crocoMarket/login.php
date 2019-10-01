<?php  
 session_start();  
 if(isset($_SESSION["user"]) && $_SESSION['prio']>50){  
    header("location:./admin/home.php");  
 }else if(isset($_SESSION["user"]) && $_SESSION['prio']<50){  
    header("location:./index.php");
 }
 
 ?>
<!DOCTYPE html>
<html >
<head>
	<meta charset="UTF-8">
	<title>Administrator login</title>
	<link rel="stylesheet" href="./admin/css/style.css"> 
	<link rel="Shortcut Icon" type="image/x-icon" href="./admin/assets/img/icon.png" />
</head>

<body>
	<div id="clouds">
		<div class="cloud x1"></div>
		<div class="cloud x2"></div>
		<div class="cloud x3"></div>
		<div class="cloud x4"></div>
		<div class="cloud x5"></div>
	</div>

	<div class="container">
		<div id="login">
			<form method="post" >
				<fieldset class="clearfix">
					<p><span class="fontawesome-user"></span><input type="text"  name="user" value="Username" onBlur="if(this.value == '') this.value = 'Username'" onFocus="if(this.value == 'Username') this.value = ''" required></p>
					<p><span class="fontawesome-lock"></span><input type="password" name="pass"  value="Password" onBlur="if(this.value == '') this.value = 'Password'" onFocus="if(this.value == 'Password') this.value = ''" required></p>
					<input type="submit" name="sub" value="Login">          
					<div class="bottom"><h3><a href="./index.php">Croco Market</a></h3></div>
				</fieldset>
			</form>
		</div>
    <img style="float:right;position:fixed;top:20%;left:150%;width:80%" src="images/croco.gif">
	</div>
</body>
</html>

<?php
   include('db.php');
  
   
   if($_SERVER["REQUEST_METHOD"] == "POST") {
      // username and password sent from form 
      
      $myusername = mysqli_real_escape_string($con,$_POST['user']);
      $mypassword = mysqli_real_escape_string($con,$_POST['pass']); 
      
      $sql = "SELECT eId FROM employee WHERE eAccount = '$myusername' and ePassword = '$mypassword'";
      $result = mysqli_query($con,$sql);
      $row = mysqli_fetch_array($result);
      $count = mysqli_num_rows($result);

      $sql_customer = "SELECT cId FROM customer WHERE cName = '$myusername' and cPassword = '$mypassword'";
      $result_customer = mysqli_query($con,$sql_customer);
      $row_customer = mysqli_fetch_array($result_customer);
      $count_customer = mysqli_num_rows($result_customer);

      // If result matched $myusername and $mypassword, table row must be 1 row
		
      if($count == 1) {
      	$_SESSION['peopleId'] = $row['eId'];
        $_SESSION['user'] = $myusername;
        $_SESSION['prio'] = 99;
        header("location: ./admin/home.php");
      }else if($count_customer == 1){
      	$_SESSION['peopleId'] = $row_customer['cId'];
      	$_SESSION['user'] = $myusername;
      	$_SESSION['prio'] = 1;
        header("location: ./index.php");
      }else {
		echo '<script>alert("Your Login Name or Password is invalid") </script>' ;
      }
   }
?>
