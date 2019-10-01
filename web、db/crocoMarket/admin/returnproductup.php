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
        $sql = "SELECT * FROM `returnproduct` WHERE id = '$id'";
        $re = mysqli_query($con,$sql);
        while($row = mysqli_fetch_array($re)){

          $rId = $row['rId'];
          $gId = $row['gId'];
          $costPrice = $row['costPrice'];
          $returnQuantity = $row['returnQuantity'];
        }
        ?>



<div class="panel-body">
                            
                            
                                            <h4 class="modal-title" id="myModalLabel">Change the ReturnProduct information</h4>
                                       
                                        <form method="post">
                                        
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Change  costPrice </label>
                                            <input name="pasd"  class="form-control" value="<?php echo $costPrice ?>">
                                            </div>
                                        </div>
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Change  Quantity </label>
                                            <input name="pawd"  class="form-control" value="<?php echo $returnQuantity ?>">
                                            </div>
                                        </div>
                                        
                                        
                                        <div class="modal-footer">
                                            <a href="./returnorder.php"><button type="button" class="btn btn-default" data-dismiss="modal">Close</button></a>
                                           <input type="submit" name="up" value="Update" class="btn btn-primary">
                                          </form>
                                           
                                        </div>
                                                       </div>
           

<?php


include ('db.php');
                    $id =$_GET['id'];

if(isset($_POST['up'])){   

                    
	               
                    $passwr = $_POST['pasd'];
                    $pawd = $_POST['pawd'];

                    $choose= "SELECT `returnQuantity`as t FROM `returnproduct` WHERE `gId`='$gId'&& rId = '$rId'";
                    $re = mysqli_query($con,$choose);
                    while($row = mysqli_fetch_array($re)){
                              $sum = $row['t'];
                    }
                    $upstoqua="UPDATE `stock` SET`quantity`=`quantity`+$sum WHERE `gId`='$gId'";
                    
                    $upsql = "UPDATE `ReturnProduct` SET `costPrice`='$passwr',`returnQuantity`='$pawd' WHERE rId = '$rId'&& gId='$gId '";
                    // $choo= "SELECT `quantity` as g FROM `stock` WHERE `gId`='$gId'";
                    // $r = mysqli_query($con,$choo);
                    // while($row = mysqli_fetch_array($r)){
                    //           $su = $row['g'];
                    // }
                    
                         $upstoquan="UPDATE `stock` SET`quantity`=`quantity`-$pawd WHERE `gId`='$gId'";
                    
                    if(mysqli_query($con,$upstoqua)&& mysqli_query($con,$upsql)&& mysqli_query($con,$upstoquan))
                    {
                    echo' <script  type="text/javascript"> alert("The Purchase Product information has update"); </script>';
                     header("Location: returnorder.php");
                    
                     }












                    
                   
                
                  
                
                }

			
			
			
		
?>

<script src="assets/js/custom-scripts.js"></script>
    
   
</body>
</html>

