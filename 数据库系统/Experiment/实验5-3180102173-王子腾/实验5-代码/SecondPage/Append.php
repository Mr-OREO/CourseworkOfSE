<?php 
    $conn = new mysqli('localhost', 'root', 'wzt75276477', 'test', '3306');
    if ($conn->connect_error) {
        die("连接失败: " . $conn->connect_error);
    }
    
    $bno = $_POST['bno'];
    $cat = $_POST['cat'];
    $tit = $_POST['tit'];
    $pre = $_POST['pre'];
    $aut = $_POST['aut'];
    $pri = $_POST['pri'];
    $yea = $_POST['yea'];
    
    $sql = "select * from book where bno='".$bno."'";
    $ERROR = false;

    $result = $conn->query($sql);

    if($row=$result->fetch_object())
    {
        $row->total++;
        $row->stock++;
    }
    else
    {
        $sql = "insert into book values('".$bno."','".$cat."','".$tit."','".$pre."',".$yea.",'".$aut."',".$pri.",1,1)";
        $result = $conn->query($sql);
        if(!$result)
        {
            $ERROR = true;
        }
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <!-- <meta http-equiv="X-UA-Compatible" content="IE=edge"> -->
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>图书管理系统</title>
    <link rel="stylesheet" href="../css/bootstrap.min.css" >
    <link rel="stylesheet" href = "../css/mainui.css">
</head>

<body class="bg-light">

    <nav class="navbar navbar-expand-lg fixed-top navbar-dark" style="background-color: #343a40;">
        <div>
            <a class="navbar-brand mr-auto mr-lg-0">Book Management System</a>
        </div>
    </nav>

    <div class="nav-scroller bg-white shadow-sm">
        <nav class="nav nav-underline">
            <a class="nav-link active" href="../FirstPage/append.html">Append</a>
            <a class="nav-link" href="../FirstPage/search.php">Search</a>
            <a class="nav-link" href="../FirstPage/borrow.php">Borrow</a>
            <a class="nav-link" href="../FirstPage/return.php">Return</a>
            <a class="nav-link" href="../FirstPage/card.php">Cards</a>
        </nav>
    </div>

<!-- feed back -->
    <div class="row">
        <?php 
            if($ERROR){
                echo  '<form class="form-signin">
                <h1 class="h3 mb-3 text-light font-weight-normal text-center">ERROR</h1>
                <div class="alert alert-danger" role="alert">"Unable to Insert"</div>
                <a class="btn btn-lg btn-dark btn-block" href="../FirstPage/append.html">Back</a>
                </form>';
            }
            else{
                echo  '<form class="form-signin">
                <h1 class="h3 mb-3 text-light font-weight-normal">Success</h1>
                <div class="alert alert-success" role="alert">"You\'ve Inserted a Book"</div>
                <a class="btn btn-lg btn-primary btn-block" href="../FirstPage/append.html">Back</a>
                </form>';
            }
        ?>
    </div>

    <script src="../js/jquery.js"></script>
    <script src="../js/mainui.js"></script>
    <script src="../js/bootstrap.min.js"></script>
</body>
</html>