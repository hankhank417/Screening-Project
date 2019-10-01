<?php
    session_start();
    include ('db.php');
    $id = $_GET['id'];
    if($id=="") {
        echo '<script>alert("Sorry ! Wrong Entry") </script>' ;
        header("Location: shop.php");
    }else{
        $sql = "SELECT bId FROM cart INNER JOIN stock ON cart.gId = stock.gId  WHERE stock.id = $id and peopleId = '".$_SESSION["peopleId"]."'";
        $result = mysqli_query($con,$sql);
        $count = mysqli_num_rows($result);
        if ($count==0) {
            $sql ="SELECT COUNT(bId) as count FROM `cart`";
            $result = mysqli_query($con, $sql);
            $row = mysqli_fetch_array($result);
            $count = $row['count'];

            $sql = "UPDATE `stock`
                    SET `clickCount` = (`clickCount`+1)
                    WHERE `id` = $id ";
            mysqli_query($con,$sql);

            $sql = "SELECT gId, gName, goodFullName, price FROM stock WHERE id=".$id;
            $result = mysqli_query($con, $sql);
            $row = mysqli_fetch_array($result);

            $sql="INSERT INTO `cart` (`bId`, `peopleId`, `gId`, `gName`, `quantity`, `price`, `goodFullName`) 
                 VALUES ( ".($count+1).", '".$_SESSION["peopleId"]."', '".$row['gId']."', '".$row['gName']."', 1, ".$row['price'].", '".$row['goodFullName']."');";
            mysqli_query($con,$sql);
        }
        header("Location: shop.php");
    }
?>