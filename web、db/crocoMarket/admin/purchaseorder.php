<?php  
session_start();  
if(!isset($_SESSION["user"]))
{
 header("location:index.php");
}
?> 
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Administrator</title>
    <link href="assets/css/bootstrap.css" rel="stylesheet" />
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.13/css/all.css" integrity="sha384-DNOHZ68U8hZfKXOrtjWvjxusGo9WQnrNx2sqG0tfsghAvtVlRW3tvkXWZh58N9jp" crossorigin="anonymous">
    <link href="assets/js/morris/morris-0.4.3.min.css" rel="stylesheet" />
    <link href="assets/css/custom-styles.css" rel="stylesheet" />
    <link href='http://fonts.googleapis.com/css?family=Open+Sans' rel='stylesheet' type='text/css' />
    <link rel="Shortcut Icon" type="image/x-icon" href="./assets/img/icon.png" />
</head>

<body>
    <div id="wrapper">
        <nav class="navbar navbar-default top-navbar" role="navigation">
            <div class="navbar-header">
                <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".sidebar-collapse">
                    <span class="sr-only">Toggle navigation</span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                </button>
                <a class="navbar-brand" href="home.php"><?php echo $_SESSION["user"]; ?> </a>
            </div>

            <ul class="nav navbar-top-links navbar-right">
                <li class="dropdown">
                    <a class="dropdown-toggle" data-toggle="dropdown" href="#" aria-expanded="false">
                        <i class="fa fa-user fa-fw"></i><i class="fa fa-caret-down"></i>
                    </a>
                    <ul class="dropdown-menu dropdown-user">
                        <li><a href="usersetting.php"><i class="fa fa-user fa-fw"></i> User Profile</a></li>
                        <li class="divider"></li>
                        <li><a href="logout.php"><i class="fa fa-sign-out fa-fw"></i> Logout</a></li>
                    </ul>
                </li>
            </ul>
        </nav>

        <nav class="navbar-default navbar-side" role="navigation">
            <div class="sidebar-collapse">
                <ul class="nav" id="main-menu">
                    <li><a href="home.php"><i class="fa fa-home fa-lg"></i>Home</a></li>
                    <li><a href="stock.php"><i class="fas fa-warehouse fa-lg"></i>Stocks list</a></li>
                    <li><a class="active-menu" href="purchaseorder.php"><i class="fab fa-wpforms fa-2x"></i>Fill Out a Purchase Form</a></li>
                    <li><a href="returnorder.php"><i class="fab fa-wpforms fa-2x"></i>Fill Out a Return Form</a></li>
                    <li><a href="tradepayment.php"><i class="fas fa-list-ul fa-2x"></i>Records</a></li>
                    <li><a href="profitChart.php"><i class="far fa-chart-bar fa-2x"></i>Profit Chart</a></li>
                    <li><a href="sendletter.php"><i class="far fa-envelope fa-2x"></i>Send Letter</a></li>
                    <li><a href="Bill.php"><i class="fas fa-qrcode fa-2x"></i>Bill</a></li>
                </ul>
            </div>
        </nav>

        <!-- /. NAV SIDE  -->
        <div id="page-wrapper" >
            <div id="page-inner">
			 
                 
               <?php
				include('db.php');
				$sql = "SELECT * FROM `supplier`";
				$re = mysqli_query($con,$sql);
				
			   ?>
            <div class="row">
                <div class="col-md-12">
                    <h1 class="page-header">
                       Supplier <small> detail</small>
                    </h1>
                </div>
                <div class="col-md-12">
                    <!-- Advanced Tables -->
                    <div class="panel panel-default">
                        <div class="panel-body">
                            <div class="table-responsive">
                                <table class="table table-striped table-bordered table-hover" id="dataTable-example">
                                    <thead>
                                        <tr>
                                            <th>sId</th>
											<th>sName</th>
                                            <th>sPhone</th>
                                            <th>sClass</th>
											<th>sAddress</th>
											<th>TaxId</th>
                                            <th>Update</th>
											<th>Remove</th>
                                            
                                        </tr>
                                    </thead>
                                    <tbody>
                                        
									<?php

                                        while($row = mysqli_fetch_array($re))
                                        {   $temp=0;
                                            
                                            
                                            $id = $row['id'];
                                            if($temp==1 && $id % 2 !=0 ){
                                                $id=$id+1;
                                            }
                                            if($temp==0 && $id % 2 ==0 ){
                                                $id=$id+1;
                                            }
                                            $sid = $row['sId'];
                                            $sName = $row['sName'];
                                            $Phone = $row['sPhone'];
                                            $Class = $row['sClass'];
                                            $Address = $row['sAddress'];
                                            $tax = $row['taxId'];
                                            
                                            if($id % 2 ==0 )
                                            {   $temp=0;
                                                echo"<tr class='gradeC'>
                                                    <td>".$sid."</td> 
                                                    <td>".$sName."</td>
                                                    <td>".$Phone."</td>
                                                    <td >".$Class."</td>
                                                    <td >".$Address."</td>
                                                    <td >".$tax."</td>
                                                    
                                                    <td><a href=supplierup.php?id=".$row['id'] ." <button class='btn btn-primary btn'
                                                    > 
                              Update 
                            </button></td>
                                                    <td><a href=supplierdel.php?id=". $row['id'] ." <button class='btn btn-danger'> <i class='fa fa-edit' ></i> Delete</button></td>
                                                     
                                                </tr>";
                                            }
                                            else
                                            {   $temp=1;
                                                echo"<tr class='gradeU'>
                                                    <td>".$sid."</td> 
                                                    <td>".$sName."</td>
                                                    <td>".$Phone."</td>
                                                    <td >".$Class."</td>
                                                    <td >".$Address."</td>
                                                    <td >".$tax."</td>
                                                    
                                                    <td><a href=supplierup.php?id=".$row['id'] ." <button class='btn btn-primary btn'
                                                    > 
                              Update 
                            </button></td>
                                                    <td><a href=supplierdel.php?id=".$row['id'] ." <button class='btn btn-danger'> <i class='fa fa-edit' ></i> Delete</button></td>
                                                    
                                                </tr>";
                                            
                                            }
                                        
                                        }
                                        
                                    ?>
                                        
                                    </tbody>
                                </table>
                            </div>
                            
                        </div>



                        </div>
                    <!--End Advanced Tables -->
                    <div class="panel-body">
                            <button class="btn btn-primary btn" data-toggle="modal" data-target="#myModal1">
                                                            Add New Supplier
                                                    </button>
                                                    
                            <div class="modal fade" id="myModal1" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
                                <div class="modal-dialog">
                                    <div class="modal-content">
                                        <div class="modal-header">
                                            <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
                                            <h4 class="modal-title" id="myModalLabel">Add the Supplier information</h4>
                                        </div>
                                        <form method="post">
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Add new Supplier Id</label>
                                            <input name="newis"  class="form-control" placeholder="Enter Supplier Id ex:(sup001)">
                                            </div>
                                        </div>
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Add new Supplier Name</label>
                                            <input name="newns"  class="form-control" placeholder="Enter Supplier Name">
                                            </div>
                                        </div>
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Add new Supplier Phone</label>
                                            <input name="newss"  class="form-control" placeholder="Enter Supplier Phone ex:(0123456789)">
                                            </div>
                                        </div>
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Add new Supplier class</label>
                                            <input name="newas"  class="form-control" placeholder="Enter Supplier class">
                                            </div>
                                        </div>
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Add new Supplier Address</label>
                                            <input name="newps"  class="form-control" placeholder="Enter Supplier Address">
                                            </div>
                                        </div>
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Add new Supplier taxId</label>
                                            <input name="newcs"  class="form-control" placeholder="Enter Supplier taxId ex:(96385527)">
                                            </div>
                                        </div>
                                        
                                        <div class="modal-footer">
                                            <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                                            
                                           <input type="submit" name="in" value="Add" class="btn btn-primary" >
                                          </form>
                                           
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                        <?php
                        if(isset($_POST['in']))
                        {
                            $temp=rand(100,1000);
                            $newis = $_POST['newis'];
                            $newns = $_POST['newns'];
                            $newss = $_POST['newss'];
                            $newas = $_POST['newas'];
                            $newps = $_POST['newps'];
                            $newcs = $_POST['newcs'];
                            $newsql="INSERT INTO `supplier`(`id`,`sId`, `sName`, `sPhone`, `sClass`, `sAddress`, `taxId`)VALUES(
                            '$temp','$newis','$newns','$newss','$newas','$newps','$newcs')";
                            if(mysqli_query($con,$newsql))
                            {
                            echo' <script  type="text/javascript"> alert("Supplier name and Id Added") ;</script>';
                             // header("Location: purchaseOrder.php");
                            
                        
                            }else{
                            echo' <script  type="text/javascript"> alert("Invalid  Added") ;</script>';
                            // header("Location: purchaseOrder.php");

                            }
                            //header("Location: messages.php");
                        }
                        ?>
                        


                      
               
                <!-- /. ROW  -->
                
                







                <?php
                $sq = "SELECT * FROM `purchaseOrder`";
                $r = mysqli_query($con,$sq);
                ?>
               <div class="row">
                <div class="col-md-12">
                        <h1 class="page-header">
                           Purchase Order
                        </h1>
                    </div>
                <div class="col-md-12">
                    <!-- Advanced Tables -->
                    <div class="panel panel-default">
                        <div class="panel-body">
                            <div class="table-responsive">
                                <table class="table table-striped table-bordered table-hover" id="dataTables-example" aria-describedby="dataTables-example_info">
                                    <thead>
                                        <tr role="row">
                                            <th tabindex="0" class="sorting" aria-controls="dataTables-example" aria-label="pId: activate to sort column ascending" rowspan="1" colspan="1">pId</th>
                                            <th tabindex="0" class="sorting_asc" aria-controls="dataTables-example" aria-label="eId: activate to sort column ascending" aria-sort="ascending" rowspan="1" colspan="1">eId</th>
                                            <th tabindex="0" class="sorting" aria-controls="dataTables-example"  aria-label="sId: activate to sort column ascending" rowspan="1" colspan="1">sId</th>
                                            <th tabindex="0" class="sorting" aria-controls="dataTables-example" aria-label="pdate: activate to sort column ascending" rowspan="1" colspan="1">pdate</th>
                                            <th tabindex="0" class="sorting" aria-controls="dataTables-example"  aria-label="Update: activate to sort column ascending" rowspan="1" colspan="1">Update</th>
                                            <th tabindex="0" class="sorting" aria-controls="dataTables-example"  aria-label="Remove: activate to sort column ascending" rowspan="1" colspan="1">Remove</th>
                                            
                                        </tr>
                                    </thead>
                                    <tbody>
                                        
                                    <?php
                                        while($row = mysqli_fetch_array($r))
                                        {   $temp=0;
                                            
                                            
                                            $id = $row['id'];
                                            if($temp==1 && $id % 2 !=0 ){
                                                $id=$id+1;
                                            }
                                            if($temp==0 && $id % 2 ==0 ){
                                                $id=$id+1;
                                            }
                                            $eId= $row['eId'];
                                            $pId = $row['pId'];
                                            $sId = $row['sId'];
                                            $pDate = $row['pDate'];
                                           
                                            
                                            if($id % 2 ==0 )
                                            {   $temp=0;
                                                echo"<tr class='gradeC'>
                                                    <td>".$pId."</td>
                                                    <td>".$eId."</td> 
                                                    <td>".$sId ."</td>
                                                    <td >".$pDate."</td>
                                            
                                                    
                                                    <td><a href=purchaseorderup.php?id=".$row['id'] ." <button class='btn btn-primary btn'
                                                    > 
                              Update 
                            </button></td>
                                                    <td><a href=purchaseorderdel.php?id=". $row['id'] ." <button class='btn btn-danger'> <i class='fa fa-edit' ></i> Delete</button></td>
                                                     
                                                </tr>";
                                            }
                                            else
                                            {   $temp=1;
                                                echo"<tr class='gradeU'>
                                                    <td>".$pId."</td>
                                                    <td>".$eId."</td>
                                                    <td>".$sId ."</td>
                                                    <td >".$pDate."</td>
                                                    
                                                    <td><a href=purchaseorderup.php?id=".$row['id'] ." <button class='btn btn-primary btn'
                                                    > 
                              Update 
                            </button></td>
                                                    <td><a href=purchaseorderdel.php?id=".$row['id'] ." <button class='btn btn-danger'> <i class='fa fa-edit' ></i> Delete</button></td>
                                                    
                                                </tr>";
                                            
                                            }
                                        
                                        }
                                        
                                    ?>
                                        
                                    </tbody>
                                </table>
                            </div>
                            
                        </div>



                        </div>
                    <!--End Advanced Tables -->
                    <div class="panel-body">
                            <button class="btn btn-primary btn" data-toggle="modal" data-target="#myModal11">
                                                            Add New PurchaseOrder
                                                    </button>
                                                    
                            <div class="modal fade" id="myModal11" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
                                <div class="modal-dialog">
                                    <div class="modal-content">
                                        <div class="modal-header">
                                            <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
                                            <h4 class="modal-title" id="myModalLabel">Add the PurchaseOrder information</h4>
                                        </div>
                                        <form method="post">
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Add  Employee Id</label>
                                            <input name="newis"  class="form-control" placeholder="Enter Employee Id ex:(emp001)">
                                            </div>
                                        </div>
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Add new PurchaseorderId </label>
                                            <input name="newns"  class="form-control" placeholder="Enter PurchaseorderId ex:(pOrder001)">
                                            </div>
                                        </div>
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Add  SupplierId</label>
                                            <input name="newss"  class="form-control" placeholder="Enter SupplierId ex:(sup001)">
                                            </div>
                                        </div>
                                       
                                        
                                        <div class="modal-footer">
                                            <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                                            
                                           <input type="submit" name="on" value="Add" class="btn btn-primary">
                                          </form>
                                           
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                        <?php
                        if(isset($_POST['on']))
                        {
                            $temp=rand(100,1000);
                            $newis = $_POST['newis'];
                            $newns = $_POST['newns'];
                            $newss = $_POST['newss'];
                            $newsql="INSERT INTO `purchaseOrder` (`id`,`eId`, `pId`, `sId`, `pDate`)VALUES(
                            '$temp','$newis','$newns','$newss',NOW())";
                            if(mysqli_query($con,$newsql))
                            {
                            echo' <script  type="text/javascript"> alert("New PurchaseOrder information Added") ;</script>';
                             
                            
                        
                            }else{
                            echo' <script  type="text/javascript"> alert("Invalid  Added") ;</script>';
                            // header("Location: messages.php");

                            }
                            //header("Location: messages.php");
                        }
                        ?>


                       



                <?php
                $sqll = "SELECT * FROM `purchaseProduct`";
                $ree = mysqli_query($con,$sqll);
                ?>
               <div class="row">
                <div class="col-md-12">
                        <h1 class="page-header">
                           Purchase Order <small> detail</small>
                        </h1>
                    </div>
                <div class="col-md-12">
                    <!-- Advanced Tables -->
                    <div class="panel panel-default">
                        <div class="panel-body">
                            <div class="table-responsive">
                                <table class="table table-striped table-bordered table-hover" id="dataTables-example3">
                                    <thead>
                                        <tr>
                                            <th>pId</th>
                                            <th>gId</th>
                                            <th>CostPrice</th>
                                            <th>Quantity</th>
                                            <th>Update</th>
                                            <th>Remove</th>
                                            
                                        </tr>
                                    </thead>
                                    <tbody>
                                        
                                    <?php
                                        while($row = mysqli_fetch_array($ree))
                                        {   $temp=0;
                                            
                                            
                                            $id = $row['id'];
                                            if($temp==1 && $id % 2 !=0 ){
                                                $id=$id+1;
                                            }
                                            if($temp==0 && $id % 2 ==0 ){
                                                $id=$id+1;
                                            }
                                            
                                            $pId = $row['pId'];
                                            $gId = $row['gId'];
                                            $CostPrice = $row['costPrice'];
                                            $Quantity = $row['purchaseQuantity'];
                                           
                                            
                                            if($id % 2 ==0 )
                                            {   $temp=0;
                                                echo"<tr class='gradeC'>
                                                    <td>".$pId."</td> 
                                                    <td>".$gId."</td>
                                                    <td>".$CostPrice ."</td>
                                                    <td >".$Quantity."</td>
                                            
                                                    
                                                     <td><a href=purchaseproductup.php?id=".$row['id'] ." <button class='btn btn-primary btn'
                                                    > 
                              Update 
                            </button></td>
                                                    <td><a href=purchaseproductdel.php?id=". $row['id'] ." <button class='btn btn-danger'> <i class='fa fa-edit' ></i> Delete</button></td>
                                                     
                                                </tr>";
                                            }
                                            else
                                            {   $temp=1;
                                                echo"<tr class='gradeU'>
                                                    <td>".$pId."</td> 
                                                    <td>".$gId."</td>
                                                    <td>".$CostPrice ."</td>
                                                    <td >".$Quantity."</td>
                                                    
                                                     <td><a href=purchaseproductup.php?id=".$row['id'] ." <button class='btn btn-primary btn'
                                                    > 
                              Update 
                            </button></td>
                                                    <td><a href=purchaseproductdel.php?id=".$row['id'] ." <button class='btn btn-danger'> <i class='fa fa-edit' ></i> Delete</button></td>
                                                    
                                                </tr>";
                                            
                                            }
                                        
                                        }
                                        
                                    ?>
                                        
                                    </tbody>
                                </table>
                            </div>
                            
                        </div>



                        </div>
                    <!--End Advanced Tables -->
                    <div class="panel-body">
                            <button class="btn btn-primary btn" data-toggle="modal" data-target="#myModal113">
                                                            Add New Purchase Product
                                                    </button>
                                                    
                            <div class="modal fade" id="myModal113" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
                                <div class="modal-dialog">
                                    <div class="modal-content">
                                        <div class="modal-header">
                                            <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
                                            <h4 class="modal-title" id="myModalLabel">Add the PurchaseProduct information</h4>
                                        </div>
                                        <form method="post">
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Add new PurchaseorderId </label>
                                            <input name="newns"  class="form-control" placeholder="Enter PurchaseorderId ex:(pOrder001)">
                                            </div>
                                        </div>
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Add  Good Id</label>
                                            <input name="newis"  class="form-control" placeholder="Enter Good Id ex:(f001)">
                                            </div>
                                        </div>
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Add  CostPrice per unit</label>
                                            <input name="newss"  class="form-control" placeholder="Enter CostPrice per unit">
                                            </div>
                                        </div>
                                        <div class="modal-body">
                                            <div class="form-group">
                                            <label>Add  Purchase Quanity</label>
                                            <input name="newws"  class="form-control" placeholder="Enter Purchase Quanity">
                                            </div>
                                        </div>
                                       
                                        
                                        <div class="modal-footer">
                                            <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                                            
                                           <input type="submit" name="onp" value="Add" class="btn btn-primary">
                                          </form>
                                           
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                        <?php
                        if(isset($_POST['onp']))
                        {
                            $temp=rand(100,1000);
                            
                            $newns = $_POST['newns'];
                            $newis = $_POST['newis'];
                            $newss = $_POST['newss'];
                            $newws = $_POST['newws'];
                            $newsql="INSERT INTO `purchaseProduct` (`id`,`pId`, `gId`, `costPrice`, `purchaseQuantity`)VALUES(
                            '$temp','$newns','$newis','$newss','$newws')";
                            $upstoquan="UPDATE `stock` SET`quantity`=`quantity`+$newws WHERE `gId`='$newis'";
                            if(mysqli_query($con,$newsql)&&mysqli_query($con,$upstoquan))
                            {
                            echo' <script  type="text/javascript"> alert("New PurchaseProduct information Added and Stock quanitity adjusted.") ;</script>';
                             
                            
                        
                            }else{
                            echo' <script  type="text/javascript"> alert("Invalid  Added and Stock quanitity fail to adjust.") ;</script>';
                            // header("Location: messages.php");

                            }
                           
                            //header("Location: messages.php");
                        }
                        ?>


                   
               
                <!-- /. ROW  -->
                


            
                    <!--End Advanced Tables -->
                </div>
            </div>







             
                                        
                                    </tbody>
                                </table>
                            </div>
                            
                        </div>
                    </div>
                    <!--End Advanced Tables -->
                </div>
            </div>
                <!-- /. ROW  -->
            
                </div>
               
            </div>
        
               
    </div>
             <!-- /. PAGE INNER  -->
            </div>
         <!-- /. PAGE WRAPPER  -->
     <!-- /. WRAPPER  -->
    <!-- JS Scripts-->
    <!-- jQuery Js -->
    <script src="assets/js/jquery-1.10.2.js"></script>
      <!-- Bootstrap Js -->
    <script src="assets/js/bootstrap.min.js"></script>
    <!-- Metis Menu Js -->
    <script src="assets/js/jquery.metisMenu.js"></script>
     <!-- DATA TABLE SCRIPTS -->
    <script src="assets/js/dataTables/jquery.dataTables.js"></script>
    <script src="assets/js/dataTables/dataTables.bootstrap.js"></script>
        <script>
            $(document).ready(function () {
                $('#dataTables-example').dataTable();
                $('#dataTable-example').dataTable();
                $('#dataTables-example3').dataTable();
              
            });
    </script>
    <script>
            function refreshPage(){
                window.location.reload();
            }
    </script>
         <!-- Custom Js -->
    <script src="assets/js/custom-scripts.js"></script>
    
   
</body>
</html>
