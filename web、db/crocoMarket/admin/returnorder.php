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
                    <li><a href="purchaseorder.php"><i class="fab fa-wpforms fa-2x"></i>Fill Out a Purchase Form</a></li>
                    <li><a class="active-menu" href="returnorder.php"><i class="fab fa-wpforms fa-2x"></i>Fill Out a Return Form</a></li>
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
				$sql = "SELECT * FROM `returnOrder`";
				$re = mysqli_query($con,$sql);
			   ?>
                <div class="row">
                    <div class="col-md-12">
                        <h1 class="page-header">
                           Return Order
                        </h1>
                    </div>
                    <div class="col-md-12">
                        <div class="panel panel-default">
                            <div class="panel-body">
                                <div class="table-responsive">
                                    <table class="table table-striped table-bordered table-hover" id="dataTable-example">
                                        <thead>
                                            <tr>
                                                <th>rId</th>
                                                <th>eId</th>
                                                <th>sId</th>
                                                <th>rDate</th>
                                                <th>Update</th>
    											<th>Remove</th>
                                            </tr>
                                        </thead>
                                        <tbody> 
    									<?php
                                            while($row = mysqli_fetch_array($re)){  
                                                $temp=0;
                                                $id = $row['id'];
                                                if($temp==1 && $id % 2 !=0 ){
                                                    $id=$id+1;
                                                }
                                                if($temp==0 && $id % 2 ==0 ){
                                                    $id=$id+1;
                                                }
                                                $eId = $row['eId'];
                                                $rId = $row['rId'];
                                                $sId = $row['sId'];
                                                $rDate = $row['rDate'];
                                                
                                                if($id % 2 ==0 ){   
                                                    $temp=0;
                                                    echo"<tr class='gradeC'>
                                                            <td>".$rId."</td>
                                                            <td>".$eId."</td> 
                                                            <td>".$sId."</td>
                                                            <td >".$rDate."</td>
                                                            <td><a href=returnorderupdate.php?id=".$row['id'] ." <button class='btn btn-primary btn'>Update</button></td>
                                                            <td><a href=returnorderdel.php?id=". $row['id'] ." <button class='btn btn-danger'> <i class='fa fa-edit' ></i> Delete</button></td>
                                                        </tr>";
                                                }
                                                else{
                                                    $temp=1;
                                                    echo"<tr class='gradeU'>
                                                            <td>".$rId."</td>
                                                            <td>".$eId."</td> 
                                                            <td>".$sId."</td>
                                                            <td >".$rDate."</td>
                                                            <td><a href=returnorderupdate.php?id=".$row['id'] ." <button class='btn btn-primary btn' >Update</button></td>
                                                            <td><a href=returnorderdel.php?id=".$row['id'] ." <button class='btn btn-danger'> <i class='fa fa-edit' ></i> Delete</button></td>
                                                        </tr>";
                                                }
                                            }
                                        ?>
                                        </tbody>
                                    </table>
                                </div>
                            </div>
                        </div>
                        <div class="panel-body">
                            <button class="btn btn-primary btn" data-toggle="modal" data-target="#myModal1">Add New returnorder</button>
                            <div class="modal fade" id="myModal1" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
                                <div class="modal-dialog">
                                    <div class="modal-content">
                                        <div class="modal-header">
                                            <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
                                            <h4 class="modal-title" id="myModalLabel">Add the Return order information</h4>
                                        </div>
                                        <form method="post">
                                            <div class="modal-body">
                                                <div class="form-group">
                                                <label>Add new Employee Id</label>
                                                <input name="newis"  class="form-control" placeholder="Enter Employee Id">
                                                </div>
                                            </div>
                                            <div class="modal-body">
                                                <div class="form-group">
                                                <label>Add new ReturnOrder Id</label>
                                                <input name="newns"  class="form-control" placeholder="Enter ReturnOrder Id">
                                                </div>
                                            </div>
                                            <div class="modal-body">
                                                <div class="form-group">
                                                <label>Add new Supplier Id</label>
                                                <input name="newss"  class="form-control" placeholder="Enter Supplier Id">
                                                </div>
                                            </div>
                                            <div class="modal-footer">
                                                <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                                                <input type="submit" name="in" value="Add" class="btn btn-primary" >
                                            </div>
                                        </form>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                    <?php
                    if(isset($_POST['in'])){
                        $temp=rand(100,1000);
                        $newis = $_POST['newis'];
                        $newns = $_POST['newns'];
                        $newss = $_POST['newss'];
                        $newsql="INSERT INTO `returnOrder` (`id`,`eId`, `rId`, `sId`, `rDate`)VALUES(
                        '$temp','$newis','$newns','$newss','2018-03-03')";
                        if(mysqli_query($con,$newsql)){
                            echo' <script  type="text/javascript"> alert("New ReturnOrder information Added") ;</script>';
                        }else{
                            echo' <script  type="text/javascript"> alert("Invalid  Added") ;</script>';
                        }
                        //header("Location: messages.php");
                    }
                    ?>

                    <?php
                    $sqll = "SELECT * FROM `returnProduct`";
                    $ree = mysqli_query($con,$sqll);
                    ?>
                    <div class="row">
                        <div class="col-md-12">
                            <h1 class="page-header">
                               Return Order <small> detail</small>
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
                                                <th>rId</th>
                                                <th>gId</th>
                                                <th>CostPrice</th>
                                                <th>returnQuantity</th>
                                                <th>Update</th>
                                                <th>Remove</th>
                                            </tr>
                                        </thead>
                                        <tbody>
                                        <?php
                                            while($row = mysqli_fetch_array($ree)){
                                                $temp=0;
                                                $id = $row['id'];
                                                if($temp==1 && $id % 2 !=0 ){
                                                    $id=$id+1;
                                                }
                                                if($temp==0 && $id % 2 ==0 ){
                                                    $id=$id+1;
                                                }
                                                
                                                $pId = $row['rId'];
                                                $gId = $row['gId'];
                                                $CostPrice = $row['costPrice'];
                                                $Quantity = $row['returnQuantity'];
                                               
                                                
                                                if($id % 2 ==0 ){
                                                    $temp=0;
                                                    echo"<tr class='gradeC'>
                                                            <td>".$pId."</td> 
                                                            <td>".$gId."</td>
                                                            <td>".$CostPrice ."</td>
                                                            <td >".$Quantity."</td>
                                                            <td><a href=returnproductup.php?id=".$row['id'] ." <button class='btn btn-primary btn'
                                                            >Update</button></td>
                                                            <td><a href=returnproductdel.php?id=". $row['id'] ." <button class='btn btn-danger'> <i class='fa fa-edit' ></i> Delete</button></td>
                                                        </tr>";
                                                }else{
                                                    $temp=1;
                                                    echo"<tr class='gradeU'>
                                                        <td>".$pId."</td> 
                                                        <td>".$gId."</td>
                                                        <td>".$CostPrice ."</td>
                                                        <td >".$Quantity."</td>
                                                        <td><a href=returnproductup.php?id=".$row['id'] ." <button class='btn btn-primary btn'>Update</button></td>
                                                        <td><a href=returnproductdel.php?id=".$row['id'] ." <button class='btn btn-danger'> <i class='fa fa-edit' ></i> Delete</button></td>
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
                            <button class="btn btn-primary btn" data-toggle="modal" data-target="#myModal113">Add New Return Product</button>
                            <div class="modal fade" id="myModal113" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
                                <div class="modal-dialog">
                                    <div class="modal-content">
                                        <div class="modal-header">
                                            <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
                                            <h4 class="modal-title" id="myModalLabel">Add the Return Product information</h4>
                                        </div>
                                        <form method="post">
                                            <div class="modal-body">
                                                <div class="form-group">
                                                <label>Add new ReturnProduct Id </label>
                                                <input name="newns"  class="form-control" placeholder="Enter Return Product Id">
                                                </div>
                                            </div>
                                            <div class="modal-body">
                                                <div class="form-group">
                                                <label>Add  Good Id</label>
                                                <input name="newis"  class="form-control" placeholder="Enter Good Id">
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
                                                <label>Add  Return Quanity</label>
                                                <input name="newws"  class="form-control" placeholder="Enter Return Quanity">
                                                </div>
                                            </div>
                                           
                                            
                                            <div class="modal-footer">
                                                <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                                                <input type="submit" name="onp" value="Add" class="btn btn-primary">
                                            </div>
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
                        $newsql="INSERT INTO `returnProduct` (`id`,`rId`, `gId`, `costPrice`, `returnQuantity`)VALUES(
                        '$temp','$newns','$newis','$newss','$newws')";
                        $upstoquan="UPDATE `stock` SET`quantity`=`quantity`-$newws WHERE `gId`='$newis'";
                        if(mysqli_query($con,$newsql)&&mysqli_query($con,$upstoquan))
                        {
                        echo' <script  type="text/javascript"> alert("New ReturnProduct information Added and Stock quanitity adjusted.") ;</script>';
                         
                        
                    
                        }else{
                        echo' <script  type="text/javascript"> alert("Invalid  Added and Stock quanitity fail to adjust.") ;</script>';
                        // header("Location: messages.php");

                        }
                       
                        //header("Location: messages.php");
                    }
                    ?>

                    <?php
                    $sq = "SELECT * FROM `stock`";
                    $reee = mysqli_query($con,$sq);
                    ?>
                    <div class="row">
                        <div class="col-md-12">
                            <h1 class="page-header">
                               Stock <small> detail</small>
                            </h1>
                        </div>
                        <div class="col-md-12">
                            <div class="panel panel-default">
                                <div class="panel-body">
                                    <div class="table-responsive">
                                        <table class="table table-striped table-bordered table-hover" id="dataTables-example4">
                                            <thead>
                                                <tr>
                                                    <th>gId</th>
                                                    <th>Quantity</th>
                                                </tr>
                                            </thead>
                                            <tbody>
                                            <?php
                                                while($row = mysqli_fetch_array($reee)){
                                                    $temp=0;
                                                    $id = $row['id'];
                                                    if($temp==1 && $id % 2 !=0 ){
                                                        $id=$id+1;
                                                    }
                                                    if($temp==0 && $id % 2 ==0 ){
                                                        $id=$id+1;
                                                    }
                                                    
                                                    $gId = $row['gId'];
                                                    $Quantity = $row['quantity'];
                                                    if($id % 2 ==0 ){   
                                                        $temp=0;
                                                        echo"<tr class='gradeC'>
                                                                <td>".$gId."</td>
                                                                <td >".$Quantity."</td>
                                                            </tr>";
                                                    }else{
                                                        $temp=1;
                                                        echo"<tr class='gradeU'>
                                                                <td>".$gId."</td>
                                                                <td >".$Quantity."</td>
                                                            </tr>";
                                                    }
                                                }
                                            ?>
                                            </tbody>
                                        </table>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                    </div>
                </div>
            </div>
        </div>
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
                $('#dataTables-example4').dataTable();
              
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
