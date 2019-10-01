<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
      <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    
    <title>SUNRISE HOTEL</title>
	<!-- Bootstrap Styles-->
    <link href="assets/css/bootstrap.css" rel="stylesheet" />
     <!-- FontAwesome Styles-->
    <link href="assets/css/font-awesome.css" rel="stylesheet" />
     <!-- Morris Chart Styles-->
   
        <!-- Custom Styles-->
    <link href="assets/css/custom-styles.css" rel="stylesheet" />
     <!-- Google Fonts-->
   <link href='http://fonts.googleapis.com/css?family=Open+Sans' rel='stylesheet' type='text/css' />
     <!-- TABLE STYLES-->
    <link href="assets/js/dataTables/dataTables.bootstrap.css" rel="stylesheet" />
    <link rel="Shortcut Icon" type="image/x-icon" href="./assets/img/icon.png" />
</head>
<body>
<?php

        include('db.php');
        $id =$_GET['id'];
        $sql = "SELECT * FROM `employee` WHERE id = '$id'";
        $re = mysqli_query($con,$sql);
        while($row = mysqli_fetch_array($re)){
          $eName = $row['eName'];
          $eAccount = $row['eAccount'];
          $ePassword = $row['ePassword'];
          
        }

         
       
        ?>
        


<div class="panel-body">
                       
                       
                           
                            
                                             <h4 class="modal-title" id="myModalLabel">Change the User Account and Password</h4>
                                       
                                        <form method="POST">
                                          <div class="modal-body">
                                                <div class="form-group">
                                                <label>Change User Name</label>
                                                <input name="userName"  class="form-control" value="<?php echo $eName ?>">
                                                </div>
                                           </div>
                                            <div class="modal-body">
                                                <div class="form-group">
                                                <label>Change User Account</label>
                                                <input name="userAccount"  class="form-control" value="<?php echo $eAccount ?>">
                                                </div>
                                           </div>
                                           <div class="modal-body">
                                                <div class="form-group">
                                                <label>Change Password</label>
                                                <input name="userPassword"  class="form-control" value="<?php echo $ePassword ?>">
                                                </div>
                                            </div>
                                            <div class="modal-footer">
                                                <a href="./usersetting.php"><button type="button" class="btn btn-default" data-dismiss="modal">Close</button></a>
                                                <input type="submit" name="up" value="Update" class="btn btn-primary">
                                            </div>
                                      </form>
                                        </div>
                                                       </div>
           

<?php 
            
  include ('db.php');




            if(isset($_POST['up'])){
              $userName = $_POST['userName'];
              $userAccount = $_POST['userAccount'];
              $userPassword = $_POST['userPassword'];
              
              $upsql = "UPDATE `employee` SET `eName`='$userName',`eAccount`='$userAccount',`ePassword`='$userPassword' WHERE id = ".$id.";";
              if(mysqli_query($con,$upsql)){
                 echo' <script language="javascript" type="text/javascript"> alert("User name and password update") </script>';
              }
                header("Location: usersetting.php");
            }
            
            ?>

<script src="assets/js/custom-scripts.js"></script>
    
   
</body>
</html>

