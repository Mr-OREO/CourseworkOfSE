<?php 
    session_start();

    $conn = new mysqli('localhost', 'root', 'wzt75276477', 'test', '3306');
    if ($conn->connect_error) {
        die("连接失败: " . $conn->connect_error);
    }

    $id = $_POST['id'];
    $pwd = $_POST['pwd'];
    $url = "search.php";
    $_SESSION['id']=$id;

    $sql = "select * from admin where admin_id='".$id."' and password = '".$pwd."' ";
    $result = $conn->query($sql);
    $info = mysqli_fetch_array($result);
 ?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>登陆</title>
    <link rel="stylesheet" href="../css/bootstrap.min.css" >
    <link rel="stylesheet" href = "../css/signin.css">
</head>

<body class="text-center">

    <?php 
        if($info == false){
            echo  '<form class="form-signin">
            <h1 class="h3 mb-3 text-light font-weight-normal">Can\'t Log In</h1>
            <div class="alert alert-danger" role="alert">"ID或PWD错误！"</div>
            <a class="btn btn-lg btn-dark btn-block" href="../FirstPage/login.html">Back</a>
            <p class="mt-5 mb-3 text-white-50"> 3180102173 -- Ziteng Wang</p>
            </form>';
        }
        else{
            echo  '<form class="form-signin">
            <h1 class="h3 mb-3 text-light font-weight-normal">Log In</h1>
            <div class="alert alert-success" role="alert">"Welcome Back！"</div>
            <a class="btn btn-lg btn-primary btn-block" href="../FirstPage/append.html">Go Ahead</a>
            <p class="mt-5 mb-3 text-white-50"> 3180102173 -- Ziteng Wang</p>
            </form>';
        }
     ?>

    <script src="../js/jquery.js"></script>
    <script src="../js/bootstrap.min.js"></script>
</body>
</html>