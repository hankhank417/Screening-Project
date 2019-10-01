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
        $sql = "SELECT * FROM `purchaseProduct` WHERE id = '$id'";
        $re = mysqli_query($con,$sql);
        while($row = mysqli_fetch_array($re)){

          $pId = $row['pId'];
          $gId = $row['gId'];
          $costPrice = $row['costPrice'];
          $purchaseQuantity = $row['purchaseQuantity'];
        }
        ?>



<div class="panel-body">
                            
                            
                                            <h4 class="modal-title" id="myModalLabel">Change the PurchaseProduct information</h4>
                                       
                                        <form method="post">
                                        
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Change costPrice </label>
                                            <input name="pasd"  class="form-control" value="<?php echo $costPrice ?>">
                                            </div>
                                        </div>
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Change Purchase Quantity</label>
                                            <input name="usph"  class="form-control" value="<?php echo $purchaseQuantity ?>">
                                            </div>
                                        </div>
                                        
                                        
                                        
                                        <div class="modal-footer">
                                            <a href="./purchaseorder.php"><button type="button" class="btn btn-default" data-dismiss="modal">Close</button></a>
                                            
                                           <input type="submit" name="upp2" value="Update" class="btn btn-primary">
                                          </form>
                                           
                                        </div>
                                    </div>
           

<?php


include ('db.php');
                    $id =$_GET['id'];

if(isset($_POST['upp2']))

                {   
                    $passwr = $_POST['pasd'];
                    $usph = $_POST['usph'];
                    $choose= "SELECT `purchaseQuantity`as t FROM `purchaseproduct` WHERE `gId`='$gId'&& pId = '$pId'";
                    $re = mysqli_query($con,$choose);
                    $sum;
                    while($row = mysqli_fetch_array($re)){
                              $sum = $row['t'];
                    }
                    $upstoqua="UPDATE `stock` SET`quantity`=`quantity`-$sum WHERE `gId`='$gId'";
                    
                    $upsql = "UPDATE `purchaseProduct` SET `costPrice`='$passwr',`purchaseQuantity`='$usph' WHERE pId = '$pId'&& gId='$gId '";
                    $upstoquan="UPDATE `stock` SET`quantity`=`quantity`+$usph WHERE `gId`='$gId'";
                    if(mysqli_query($con,$upstoqua)&& mysqli_query($con,$upsql)&& mysqli_query($con,$upstoquan))
                    {
                    echo' <script  type="text/javascript"> alert("The Purchase Product information has update"); </script>';
                    
                
                    }
                
                header("Location: purchaseorder.php");
                
                }
			
			
			
		
?>

<script src="assets/js/custom-scripts.js"></script>
    
   
</body>
</html>