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
        $sql = "SELECT * FROM `supplier` WHERE id = '$id'";
        $re = mysqli_query($con,$sql);
        while($row = mysqli_fetch_array($re)){

          $sid = $row['sId'];
          $sName = $row['sName'];
          $Phone = $row['sPhone'];
          $Class = $row['sClass'];
          $Address = $row['sAddress'];
          $tax = $row['taxId'];
        }
        ?>


<?php


include ('db.php');
                    $id =$_GET['id'];
                if(isset($_POST['up']))

                {   
                    $usacc = $_POST['usacc'];
                    $passwr = $_POST['pasd'];
                    $usph = $_POST['usph'];
                    $usadd = $_POST['usadd'];
                    $ustax = $_POST['ustax'];
                    
                    $upsql = "UPDATE `supplier` SET `sName`='$usacc',`sPhone`='$passwr',`sClass`='$usph',`sAddress`='$usadd',`taxId`='$ustax' WHERE sId = '$sid'";
                    if(mysqli_query($con,$upsql))
                    {
                    echo' <script  type="text/javascript"> alert("User name and password update"); </script>';
                    
                     header("Location: purchaseorder.php");
                    }
                 
                 
                
                
                }
            
            
        
?>

<div class="panel-body">
                            
                            
                                            <h4 class="modal-title" id="myModalLabel">Change the Supplier information</h4>
                                       
                                       <form method="post">
                                        
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Change Supplier Name</label>
                                            <input name="usacc"  class="form-control" value="<?php echo $sName ?>">
                                            </div>
                                        </div>
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Change Supplier Phone</label>
                                            <input name="pasd"  class="form-control" value="<?php echo $Phone ?>">
                                            </div>
                                        </div>
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Change Supplier Class</label>
                                            <input name="usph"  class="form-control" value="<?php echo $Class?>">
                                            </div>
                                        </div>
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Change Supplier Address</label>
                                            <input name="usadd"  class="form-control" value="<?php echo $Address ?>">
                                            </div>
                                        </div>
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Change Supplier taxId</label>
                                            <input name="ustax"  class="form-control" value="<?php echo $tax ?>">
                                            </div>
                                        </div>
                                        
                                        <div class="modal-footer">
                                            <a href="./purchaseorder.php"><button type="button" class="btn btn-default" data-dismiss="modal">Close</button></a>
                                           <input type="submit" name="up" value="Update" class="btn btn-primary">
                                          </form>
                                           
                                        </div>
                                    </div>

<script src="assets/js/custom-scripts.js"></script>
    
   
</body>
</html>