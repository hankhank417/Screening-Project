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
                    <li><a href="returnorder.php"><i class="fab fa-wpforms fa-2x"></i>Fill Out a Return Form</a></li>
                    <li><a href="tradepayment.php"><i class="fas fa-list-ul fa-2x"></i>Records</a></li>
                    <li><a href="profitChart.php"><i class="far fa-chart-bar fa-2x"></i>Profit Chart</a></li>
                    <li><a href="sendletter.php"><i class="far fa-envelope fa-2x"></i>Send Letter</a></li>
                    <li><a class="active-menu" href="Bill.php"><i class="fas fa-qrcode fa-2x"></i>Bill</a></li>
                </ul>
            </div>
        </nav>
        <!-- /. NAV SIDE  -->
        <div id="page-wrapper" >
            <div id="page-inner">
                <div class="row">
                    <div class="col-md-12">
                        <h1 class="page-header">
                            Transaction<small> Bill</small>
                        </h1>
                    </div>
                </div>
                <div class="row">
                    <div class="col-md-12">
                        <?php
                            include('db.php');
                            $sql = "SELECT gName,quantity,price FROM stock WHERE stock.quantity>0";
                            $re = mysqli_query($con,$sql);
                        ?>
                        <div class="row">
                            <div class="col-md-12">
                                <div class="panel panel-primary">
                                    <div class="panel-heading">
                                        BILL
                                    </div>
                                    <div class="panel-body">
                                        <form name="form" method="post">
                                            <div class="form-group">
                                                <label>Now Stock</label>
                                                <select name="object" class="form-control">
                                                    <?php while ($row = mysqli_fetch_array($re)) { ?>
                                                        <option name="choice" value="<?php echo $row['gName']?>"> <?php echo $row['gName']."&nbsp;&nbsp;&nbsp;$".$row['price']."&nbsp;&nbsp;&nbsp;".$row['quantity']."個"; ?>
                                                    <?php } ?>
                                                        </option>
                                                </select>
                                            </div>
                                            <div class="form-group">
                                                <label>Number</label>
                                                <input type="text" name="num" class="form-control">
                                            </div>
                                            <div class="form-group">
                                                <label>Customer</label>
                                                <select name="cId" class="form-control">
                                                    <?php 
                                                        $sql = "SELECT cId FROM customer";
                                                        $re = mysqli_query($con,$sql);
                                                        while ($row = mysqli_fetch_array($re)) { ?>
                                                            <option value="<?php echo $row['cId']?>"> <?php echo $row['cId']; ?>
                                                        <?php } 
                                                    ?>
                                                        </option>
                                                </select>
                                            </div>
                                            <div class="form-group">
                                                <label>Employee</label>
                                                <select name="eId" class="form-control">
                                                    <?php 
                                                        $sql = "SELECT eId FROM employee";
                                                        $re = mysqli_query($con,$sql);
                                                        while ($row = mysqli_fetch_array($re)) { ?>
                                                            <option value="<?php echo $row['eId']?>"> <?php echo $row['eId']; ?>
                                                        <?php } 
                                                    ?>
                                                        </option>
                                                </select>
                                            </div>
                                            <input type="submit" name="bill" value="submit" class="btn btn-primary">
                                        </form>
                                        <?php
                                        include('db.php');
                                        if(isset($_POST['bill'])){
                                            include('db.php');
                                            $object = $_POST['object'];
                                            $num = $_POST['num'];
                                            $cId = $_POST['cId'];
                                            $eId = $_POST['eId'];

                                            $sql="SELECT quantity,gName FROM stock WHERE gName='".$object."'";
                                            $stockQunantity=mysqli_query($con,$sql);
                                            if (!$stockQunantity) {
                                             printf("Error: %s\n", mysqli_error($con));
                                             exit();
                                            }
                                            $legal = true;
                                            $newNum = 0;
                                            while ($result=mysqli_fetch_array($stockQunantity)) {
                                                if (($result['quantity']-$num)>=0) {
                                                    $newNum=$result['quantity']-$num;
                                                }else{
                                                    $legal=false;
                                                    echo "<br>Insert failed.";
                                                }
                                                
                                            };
                                            if ($legal) {
                                                $returnBill="UPDATE stock SET quantity=".$newNum." WHERE gName='".$object."'";
                                                $a = mysqli_query($con,$returnBill);

                                                $sql ="SELECT COUNT(id) as count FROM trade";
                                                $result = mysqli_query($con, $sql);
                                                $row = mysqli_fetch_array($result);
                                                $count = $row['count'];
                                                
                                                $sql ="SELECT COUNT(*) as tcount FROM (SELECT tId FROM trade GROUP BY tId) as tradetable";
                                                $result = mysqli_query($con, $sql);
                                                $row = mysqli_fetch_array($result);
                                                $tcount = $row['tcount'];

                                                $sql="INSERT INTO `transactionDetails`(`id`,`cId`,`tId`,`eId`) VALUES ( ".($tcount+1).",'".$cId."' , 'tran".($tcount+1)."' ,'".$eId."'  );";
                                                $b = mysqli_query($con,$sql);

                                                $gIdSearchSql="SELECT gId FROM stock WHERE gName='".$object."'";
                                                $gIdSearch=mysqli_query($con,$gIdSearchSql);
                                                $gId;
                                                while ($result=mysqli_fetch_array($gIdSearch)) {
                                                    $gId=$result['gId'];
                                                };


                                                $sq="INSERT INTO `trade`(`id`,`tId`,`gId`,`quantity`,`tradeTime`) 
                                                    VALUES ( ".($count+1).",'tran".($tcount+1)."' ,'".$gId."' ,".$num.", NOW());";
                                                if (mysqli_query($con,$sq)) {
                                                    echo "<br>Insert successfully";
                                                }
                                            }
                                        }
                                        
                                        ?>
                                    </div>
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
