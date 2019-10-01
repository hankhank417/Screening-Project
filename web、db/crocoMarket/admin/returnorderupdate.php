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
        $sql = "SELECT * FROM `returnorder` WHERE id = '$id'";
        $re = mysqli_query($con,$sql);
        while($row = mysqli_fetch_array($re)){

          $eId = $row['eId'];
          $rId = $row['rId'];
          $sId = $row['sId'];
        }

         
       
        ?>
        


<div class="panel-body">
                       
                       
                           
                            
                                            <h4 class="modal-title" id="myModalLabel">Change the Return order information</h4>
                                       
                                        <form method="post">
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Change Employee Id </label>
                                             
                                              <input  name="upid" class="form-control" value="<?php echo $eId ?>" > 
                                                
                                            </div>
                                        </div>
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Change  supplier Id </label>
                                        
                                                    <input  name="pasd"  class="form-control" value="<?php echo $sId ?>" > 
                                               
                                            </div>
                                        </div>
                                        
                                        
                                        <div class="modal-footer">
                                            <a href="./returnorder.php"><button type="button" class="btn btn-default" data-dismiss="modal">Close</button></<a>
                                            
                                           <input type="submit" name="up" value="Update" class="btn btn-primary">
                                          </form>
                                           
                                        </div>
                                                       </div>
           

<?php


include ('db.php');
                    $id =$_GET['id'];

if(isset($_POST['up'])){   

                    
	                $upid = $_POST['upid'];
                    $passwr = $_POST['pasd'];
                    
                    $upsql = "UPDATE `returnorder` SET `eId`='$upid',`rId`='$rId',`sId`=' $passwr' WHERE id = '$id'";
                    if(mysqli_query($con,$upsql))
                    {
                    echo' <script  type="text/javascript"> alert("Return Order update"); </script>';
                    
                
                    }
                
                   header("Location: returnorder.php");
                
                }

			
			
			
		
?>

<script src="assets/js/custom-scripts.js"></script>
    
   
</body>
</html>

