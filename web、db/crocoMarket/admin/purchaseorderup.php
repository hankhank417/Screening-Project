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
        $sql = "SELECT * FROM `purchaseOrder` WHERE id = '$id'";
        $re = mysqli_query($con,$sql);
        while($row = mysqli_fetch_array($re)){

          $eId = $row['eId'];
          $pId = $row['pId'];
          $sId = $row['sId'];
          $pDate = $row['pDate'];
         
        }
    ?>
    <div class="panel-body">
        <h4 class="modal-title" id="myModalLabel">Change the Purchase Order information</h4>
        <form method="post">
            <div class="modal-body">
                <div class="form-group">
                    <label>Change Employee Id</label>
                    <input name="usacc"  class="form-control"  value="<?php echo $eId ?>">
                </div>
            </div>
            <div class="modal-body">
                <div class="form-group">
                    <label>Change Supplier Id</label>
                    <input name="pasd"  class="form-control"  value="<?php echo $sId ?>">
                </div>
            </div>
            <div class="modal-footer">
                <a href="./purchaseorder.php"><button type="button" class="btn btn-default" data-dismiss="modal">Close</button></a>
                <input type="submit" name="up2" value="Update" class="btn btn-primary">
            </div>
        </form>
    </div>
    <?php 
    if(isset($_POST['up2'])){   
        $usacc = $_POST['usacc'];
        $passwr = $_POST['pasd'];
        
        
        
        
        $upsql = "UPDATE `purchaseOrder` SET `eId`='$usacc',`sId`='$passwr' WHERE pId = '$pId'";
        if(mysqli_query($con,$upsql))
        {
        echo' <script  type="text/javascript"> alert("The Purchase Order information update"); </script>';
        
    
        }
    
    header("Location: ./purchaseorder.php");
    
    }
    ?>
    <script src="assets/js/custom-scripts.js"></script>
</body>
</html>