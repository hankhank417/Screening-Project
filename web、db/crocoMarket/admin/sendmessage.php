<?php
  include('db.php');
  $mai = "SELECT * FROM `contact`";
  $rew = mysqli_query($con,$mai);
  $mailSub=$_POST['subject'];
  $mailMsg=$_POST['news'];
  require 'PHPMailer-master/PHPMailerAutoload.php';
  while($rows = mysqli_fetch_array($rew)){
    if($rows['approval']=="Allowed"){
      $mailto = $rows['email'];
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
      $mail ->Body = $mailMsg;
      $mail ->AddAddress($mailto);

      if(!$mail->Send()){
        echo "Mail Not Sent";
        echo "<br>";
      }else{
        echo "Mail Sent";
        echo "<br>";
      }
    }
  }
  sleep(10);
  header("Location: sendletter.php");
?>