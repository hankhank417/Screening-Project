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
                    <li><a class="active-menu" href="stock.php"><i class="fas fa-warehouse fa-lg"></i>Stocks list</a></li>
                    <li><a href="purchaseorder.php"><i class="fab fa-wpforms fa-2x"></i>Fill Out a Purchase Form</a></li>
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
                <div class="row">
                    <div class="col-md-12">
                        <h1 class="page-header">
                            Stock List <small></small>
                        </h1>
                    </div>
                </div> 

                <div class="row">
                    <div class="col-md-4 col-sm-4">
                        <div class="panel panel-primary">
                            <div class="panel-heading">
                                ADD NEW STOCK
                            </div>
                            <div class="panel-body">
                                <form name="form" method="post" enctype="multipart/form-data">
                                    <div class="form-group">
                                        <label>Type Of Stock<span style="color: red;"> *</span></label>
                                        <input name="newType"  class="form-control">
                                    </div>
                                      
                                    <div class="form-group">
                                        <label>Name<span style="color: red;"> *</span></label>
                                        <input name="newName"  class="form-control">
                                    </div>
                                    <div class="form-group">
                                        <label>Quantity<span style="color: red;"> *</span></label>
                                        <input name="newQuantity"  class="form-control">
                                    </div>
                                    <div class="form-group">
                                        <label>Price<span style="color: red;"> *</span></label>
                                        <input name="newPrice"  class="form-control">
                                    </div>
                                    <div class="form-group">
                                        <label>Picture<span style="color: red;"> *</span></label>
                                        <input type="file" accept="image/*" name="uploadImg">
                                    </div>
                                    <input type="submit" name="add" value="Add New" class="btn btn-primary"> 
                                </form>
                                <?php
                                include('db.php');
                                if(isset($_POST['add'])){
                                    $goodFullName = $_POST['newType'];
                                    $type = substr("$goodFullName", 0, 1);
                                    $name = $_POST['newName'];
                                    $quantity = $_POST['newQuantity'];
                                    $price = $_POST['newPrice'];

                                    if (!empty($goodFullName) && !empty($name) && !empty($quantity) && !empty($price) && !empty($_FILES["uploadImg"]["name"])) {
                                        $sql ="SELECT COUNT(gId) as count FROM stock";
                                        $result = mysqli_query($con, $sql);
                                        $row = mysqli_fetch_array($result);
                                        $count = $row['count'];
                                        $sql ="SELECT COUNT(SUBSTR(gId, 1, 1)) as count FROM stock WHERE SUBSTR(gId, 1, 1)='".$type."'";
                                        $result = mysqli_query($con, $sql);
                                        $row = mysqli_fetch_array($result);
                                        $gCount = $row['count'];

                                        $sql = "INSERT INTO `stock`(`id`,`gId`,`quantity`,`gName`,`price`, `goodFullName`, `clickCount`) VALUES ( ".($count+1).", '$type".($gCount+1)."', $quantity,'$name', $price, '$goodFullName', 0);";
                                        if (!mysqli_query($con,$sql)) {
                                            echo '<script>alert("Add new stock failed.") </script>' ;
                                        }

                                        $target_dir = "list";
                                        $tmpfile = $_FILES["uploadImg"]["tmp_name"];
                                        if(!move_uploaded_file($tmpfile, "$target_dir/$name.jpg")){
                                            echo "<script>alert(".$_FILES['uploadImg']['error'].")</script>";
                                        }else{
                                            $sql = "INSERT INTO `imageList`(`name`,`dir`) VALUES ('".$name."', 'list/".$name.".jpg');";
                                            mysqli_query($con,$sql);
                                        }
                                    }
                                }
                                
                                ?>
                            </div>
                        </div>

                        <div class="panel panel-primary">
                            <div class="panel-heading">
                                UPDATE STOCK
                            </div>
                            <div class="panel-body">
                                <form name="form" method="post" enctype="multipart/form-data">
                                    <div class="form-group">
                                        <label>Stock no. <span style="color: red;">*</span></label>
                                        <input name="gId"  class="form-control">
                                    </div>
                                      
                                    <div class="form-group">
                                        <label>Name</label>
                                        <input name="name"  class="form-control">
                                    </div>
                                    <div class="form-group">
                                        <label>Quantity</label>
                                        <input name="quantity"  class="form-control">
                                    </div>
                                    <div class="form-group">
                                        <label>Price</label>
                                        <input name="price"  class="form-control">
                                    </div>
                                    <div class="form-group">
                                        <label>Picture</label>
                                        <input type="file" accept="image/*" name="updateImg">
                                    </div>
                                    <input type="submit" name="update" value="Update" class="btn btn-primary">
                                </form>
                                <?php
                                include('db.php');
                                if(isset($_POST['update'])){
                                    $gId = $_POST['gId'];
                                    $name = $_POST['name'];
                                    $quantity = $_POST['quantity'];
                                    $price = $_POST['price'];
                                    if (!empty($name)) {
                                        $imgSql = "UPDATE imageList SET name = '".$name."' WHERE name IN (
                                                        SELECT a.name FROM ( SELECT * FROM imageList ) a INNER JOIN stock b on a.name = b.gName WHERE b.gId='".$gId."')";
                                        if (mysqli_query($con,$imgSql)) {
                                            $sql = "UPDATE `stock` SET `gName`='".$name."' WHERE `gId` = '".$gId."'";
                                            mysqli_query($con,$sql);
                                        }
                                    }
                                    if (!empty($quantity)) {
                                        $sql = "UPDATE `stock`
                                            SET `quantity`=".$quantity."
                                            WHERE `gId` = '".$gId."'";
                                        mysqli_query($con,$sql);
                                    }
                                    if (!empty($price)) {
                                        $sql = "UPDATE `stock`
                                            SET `price`=".$price."
                                            WHERE `gId` = '".$gId."'";
                                        mysqli_query($con,$sql);
                                    }

                                    if(!empty($_FILES["updateImg"]["name"])){
                                        $updateImgName = "SELECT imageList.name FROM imageList INNER JOIN stock ON imageList.name=stock.gName WHERE stock.gId='".$gId."'";
                                        $result = mysqli_query($con,$updateImgName);
                                        while($row = mysqli_fetch_array($result))  $imgName = $row['name'];

                                        $imgSql = "UPDATE imageList SET dir = 'list/".$imgName.".jpg' WHERE name='".$imgName."'";
                                        mysqli_query($con,$imgSql);

                                        $target_dir = "list";
                                        $tmpfile = $_FILES["updateImg"]["tmp_name"];
                                        move_uploaded_file($tmpfile, "$target_dir/$imgName.jpg");
                                    }
                                }
                                
                                ?>
                            </div>
                        </div>

                        <div class="panel panel-primary">
                            <div class="panel-heading">
                                DELETE STOCK
                            </div>
                            <div class="panel-body">
                                <form name="form" method="post">
                                    <div class="form-group">
                                        <label>Stock no. <span style="color: red;">*</span></label>
                                        <input name="delGId"  class="form-control">
                                    </div>
                                    <input type="submit" name="del" value="Delete" class="btn btn-primary"> 
                                </form>
                                <?php
                                include('db.php');
                                if(isset($_POST['del'])){
                                    include('db.php');
                                    $gId = $_POST['delGId'];
                                    $sql = "DELETE FROM `stock` WHERE gId='".$gId."'";
                                    mysqli_query($con, $sql);
                                }
                                
                                ?>
                            </div>
                        </div>
                    </div>
                    <div class="col-md-8 col-sm-8">
                        <div class="panel panel-primary">
                            <div class="panel-heading">
                                STOCKS INFORMATION
                            </div>
                            <div class="panel-body">
                                <div class="panel panel-default">
                                    <?php
                                        $sql = "select * from stock limit 0,10";
                                        $re = mysqli_query($con,$sql)
                                    ?>
                                    <div class="panel-body">
                                        <div class="table-responsive">
                                            <table class="table table-striped table-bordered table-hover" id="dataTables-example">
                                                <thead>
                                                    <tr>
                                                        <th>Stock no.</th>
                                                        <th>Product Name</th>
                                                        <th>quantity</th>
                                                        <th>Price</th>
                                                        <th>Click Count</th>
                                                    </tr>
                                                </thead>
                                                <tbody>
                                                
                                                <?php
                                                include('db.php');
                                                $sql = "SELECT * FROM stock";
                                                $re = mysqli_query($con,$sql);
                                                $id=0;
                                                while($row = mysqli_fetch_array($re)){
                                                    $id = $id+1;
                                                    if($id % 2 ==1 ){
                                                        echo"<tr class='gradeC'>
                                                                <td>".$row['gId']."</td>
                                                                <td>".$row['gName']."</td>
                                                                <td>".$row['quantity']."</td>
                                                                <td>".$row['price']."</td>
                                                                <td>".$row['clickCount']."</td>
                                                            </tr>";
                                                    }else{
                                                        echo"<tr class='gradeU'>
                                                                <td>".$row['gId']."</td>
                                                                <td>".$row['gName']."</td>
                                                                <td>".$row['quantity']."</td>
                                                                <td>".$row['price']."</td>
                                                                <td>".$row['clickCount']."</td>
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
