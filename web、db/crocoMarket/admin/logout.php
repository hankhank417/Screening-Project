<?php
session_start();
unset($_SESSION["user"]);
unset($_SESSION["peopleId"]);
unset($_SESSION["prio"]);
header("location:../index.php");
?>