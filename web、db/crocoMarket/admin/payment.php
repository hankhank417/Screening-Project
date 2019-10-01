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
                    <li><a href="purchaseOrder.php"><i class="fab fa-wpforms fa-2x"></i>Fill Out a Purchase Form</a></li>
                    <li><a href="returnorder.php"><i class="fab fa-wpforms fa-2x"></i>Fill Out a Return Form</a></li>
                    <li><a class="active-menu" href="tradepayment.php"><i class="fas fa-list-ul fa-2x"></i>Records</a></li>
                    <li><a href="profitChart.php"><i class="far fa-chart-bar fa-2x"></i>Profit Chart</a></li>
                    <li><a href="sendletter.php"><i class="far fa-envelope fa-2x"></i>Send Letter</a></li>
                    <li><a href="Bill.php"><i class="fas fa-qrcode fa-2x"></i>Bill</a></li>
                </ul>
            </div>
        </nav>
        <!-- /. NAV SIDE  -->
        <div id="page-wrapper" >
            <div id="page-inner">
    			<div class="row">
                    <div class="col-md-12">
                        <h1 class="page-header">
                           Print Purchase Payment Details<small> </small>
                        </h1>
                    </div>
                </div> 				 
    				 
                <div class="row">
                    <div class="col-md-12">
                        <a href="tradepayment.php" class='btn btn-primary'><i class='far fa-chart-bar'></i>  Trade</a>
                        <a href="payment.php" class='btn btn-primary'><i class='far fa-chart-bar'></i>  Purchase</a>
                        <a href="returnpayment.php" class='btn btn-primary'><i class='far fa-chart-bar'></i>  Return</a>
                        <br><br><br>
                        <div class="panel panel-default">
                            <div class="panel-body">
                                <div class="table-responsive">
                                    <table class="table table-striped table-bordered table-hover" id="dataTables-example">
                                        <thead>
                                            <tr>
                                                <th>Purchase ID</th>
    											<th>Employee ID</th>
    											<th>Supplier ID</th>
    											<th>Purchase Date</th>
    											<th>Print</th>
                                            </tr>
                                        </thead>
                                        <tbody>
    									<?php
    										include ('db.php');
    										$sql="SELECT `purchaseProduct`.`id` ,`purchaseProduct`.`pId` , `purchaseOrder`.`eId`,`purchaseOrder`.`sId`,`purchaseOrder`.`pDate` 
                                                  FROM `purchaseProduct`INNER JOIN`purchaseOrder` on `purchaseProduct`.`pId`=`purchaseOrder`.`pId`
                                                  GROUP BY pId";
    										$re = mysqli_query($con,$sql);
    										while($row = mysqli_fetch_array($re))
    										{
    										
    											$temp=0;
                                                
                                                
                                                $id = $row['id'];
                                                if($temp==1 && $id % 2 !=0 ){
                                                    $id=$id+1;
                                                }
                                                if($temp==0 && $id % 2 ==0 ){
                                                    $id=$id+1;
                                                }
    											
    											if($id % 2 ==1 )
    											{   $temp=0;
    												echo"<tr class='gradeC'>
    													<td>".$row['pId']."</td>
    													<td>".$row['eId']."</td>
    													<td>".$row['sId']."</td>
    													<td>".$row['pDate']."</td>
    													<td><a href=printnew.php?pid=".$row['id'] ." <button class='btn btn-primary'> <i class='fa fa-print' ></i> Print</button></td>
    													</tr>";
    											}
    											else
    											{   $temp=1;
    												echo"<tr class='gradeU'>
    													<td>".$row['pId']."</td>
                                                        <td>".$row['eId']."</td>
                                                        <td>".$row['sId']."</td>
                                                        <td>".$row['pDate']."</td>
    													<td><a href=printnew.php?pid=".$row['id']." <button class='btn btn-primary'> <i class='fa fa-print' ></i> Print</button></td>
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
            });
    </script>
         <!-- Custom Js -->
    <script src="assets/js/custom-scripts.js"></script>
    
   
</body>
</html>


