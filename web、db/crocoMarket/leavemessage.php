<?php
include('db.php');
require 'PHPMailer-master/PHPMailerAutoload.php';

$name =$_POST['name'];
$phone = $_POST['phone'];
$email = $_POST['emailname'];
$message = $_POST['message'];
$subject =$_POST['subject'];
$approval = "Not Allowed";
$temp=rand(100,10000);

$sql = "SELECT id FROM contact WHERE email = '".$email."'";
$result = mysqli_query($con,$sql);
$count = mysqli_num_rows($result);
if ($count ==0 ) {
	$sql = "INSERT INTO `contact`(`fullname`, `phoneno`, `email`,`cdate`,`approval`) VALUES ('$name','$phone','$email',now(),'$approval')" ;
	if(mysqli_query($con,$sql)) echo"Insert OK";
}else{
	$sql = "INSERT INTO `contact`(`fullname`, `phoneno`, `email`,`cdate`,`approval`) VALUES ('$name','$phone','$email',now(),'$approval')" ;
	if(mysqli_query($con,$sql)) echo"Update OK";
}
  

$mailSub=$subject;
$mailMsg='Customer_Name：'.$name.'<br>'.
'Customer_Email：'.$email.'<br>'.
'Customer_Phone：'.$phone.'<br>'.
'Customer_Comment：'.$message.'<br>';

$mailto = "crocomarket@gmail.com";
$mail = new PHPMailer();
$mail ->IsSmtp();
$mail ->SMTPDebug = 1;
$mail ->SMTPAuth = true;
$mail ->SMTPSecure = 'ssl';
$mail ->Host = "smtp.gmail.com";
$mail ->Port = 465; // or 587
$mail ->IsHTML(true);
$mail ->Username = "crocomarket@gmail.com";
$mail ->Password = "crococroco";
$mail ->SetFrom("crocomarket@gmail.com");
$mail ->Subject = $mailSub;
$mail ->Body = nl2br($mailMsg);
$mail ->AddAddress($mailto);
$mail->AddAttachment('croco.png');

if(!$mail->Send()){
    echo "Mail Not Sent";
    echo "\n";
  }else{
    echo "Mail Sent";
    echo "\n";
}