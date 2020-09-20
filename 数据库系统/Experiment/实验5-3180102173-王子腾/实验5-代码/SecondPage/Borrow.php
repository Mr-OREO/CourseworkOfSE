<?php 
    session_start();
    $id = $_SESSION['id'];
    
    $conn = new mysqli('localhost', 'root', 'wzt75276477', 'test', '3306');
    if ($conn->connect_error) {
        die("连接失败: " . $conn->connect_error);
    }

    $cno = $_POST['cno'];
    $bno = $_POST['bno'];
    $showcard = false;
    $ERROR=0;

    $sql = "select * from card where cno='".$cno."'";
    $result=$conn->query($sql);
    $row=$result->fetch_array();
    if(!$row)
    {
        $ERROR=1;// 借书证不存在
    }
    else if($bno=="")// Show borrowed by cno
    {
        $showcard = true;
    }
    else{       // Borrow book
        $sql="select * from borrow where cno='".$cno."' and bno='".$bno."' and return_date is null";
        $result=$conn->query($sql);

        if($result->fetch_object()){
            $ERROR=2;// 该用户已借过这本书了
        }
        else{
            $sql="select * from book where bno='".$bno."'";
            $result=$conn->query($sql);
            $check=$result->fetch_object();
            if($check->stock<=0)
            {
                $ERROR=3;// 库存0
            }
            else{
                $sql="update book set stock = stock-1 where bno='".$bno."'";
                if(!($result=$conn->query($sql)))
                {
                    $ERROR=4;// SQL查询失败
                }
                else
                {   $sql="insert into borrow values('".$cno."','".$bno."','".date("Y-m-d")."',null,'".$id."')";
                    if(!($result=$conn->query($sql)))
                    {
                        $ERROR=4;// SQL查询失败
                    }
                }
            }
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
            <a class="nav-link" href="../FirstPage/append.html">Append</a>
            <a class="nav-link" href="../FirstPage/search.php">Search</a>
            <a class="nav-link active" href="../FirstPage/borrow.php">Borrow</a>
            <a class="nav-link" href="../FirstPage/return.php">Return</a>
            <a class="nav-link" href="../FirstPage/card.php">Cards</a>
        </nav>
    </div>

    <?php
        switch($ERROR)
        {
            case 1:
                echo  '<form class="form-signin">
            <h1 class="h3 mb-3 text-light font-weight-normal">ERROR</h1>
            <div class="alert alert-danger" role="alert">"Card NOT EXIST"</div>
            <a class="btn btn-lg btn-dark btn-block" href="../FirstPage/borrow.php">Back</a>
            </form>';
                return;
            case 2:
                echo  '<form class="form-signin">
            <h1 class="h3 mb-3 text-light font-weight-normal">Cannot Borrow</h1>
            <div class="alert alert-danger" role="alert">"You Already Have One"</div>
            <a class="btn btn-lg btn-dark btn-block" href="../FirstPage/borrow.php">Back</a>
            </form>';
                return;
            case 3:
                $sql="select return_date from borrow where bno = '".$bno."' order by return_date desc";
                $result=$conn->query($sql);
                $info=$result->fetch_array();
                $last_re_date = $info[0];
                echo  '<form class="form-signin">
            <h1 class="h3 mb-3 text-light font-weight-normal">No Storage</h1>
            <div class="alert alert-danger" role="alert">"The Book Has No Storage Now"</div>
            <div class="alert alert-dark" role="alert">"Last Return is at".<?php echo"$last_re_date"?></div>
            <a class="btn btn-lg btn-dark btn-block" href="../FirstPage/borrow.php">Back</a>
            </form>';
                return;
            case 4:
                echo  '<form class="form-signin">
            <h1 class="h3 mb-3 text-light font-weight-normal">ERROR</h1>
            <div class="alert alert-danger" role="alert">"MySQL ERROR"</div>
            <a class="btn btn-lg btn-dark btn-block" href="../FirstPage/borrow.php">Back</a>
            </form>';
                return;
        }
    ?>

<div class="row">
    <div class="col-md-4 order-md-1">
        <form class="form-signin ">
            <h1 class="h3 mb-3 text-light font-weight-normal">Check</h1>
            <?php 
                if($showcard)
                {
                    echo  '<div class="alert alert-info" role="alert">"Borrow Infomation"</div>
                <a class="btn btn-lg btn-info btn-block" href="../FirstPage/borrow.php">Back</a>';
                }
                else{
                    echo  '<div class="alert alert-info" role="alert">"You\'ve borrowed a new book"</div>
                <a class="btn btn-lg btn-info btn-block" href="../FirstPage/borrow.php">Back</a>';
                }
            ?>
        </form>
    </div>

    <div class="col-md-7 order-md-2 text-center">
        <table class="table text-light h5">
            <thead>
                <tr>
                <th scope="col">cno</th>
                <th scope="col">bno</th>
                <th scope="col">borrow_date</th>
                <th scope="col">return_date</th>
                <th scope="col">done_by</th>
                </tr>
            </thead>
            <tbody>
                <?php 
                    $sql="select * from borrow where cno='".$cno."'";
                    $result=$conn->query($sql);
                    while($row=$result->fetch_object())
                    {
                        echo '
                        <tr>
                        <td>'.$row->cno.'</td>
                        <td>'.$row->bno.'</td>
                        <td>'.$row->borrow_date.'</td>
                        <td>'.$row->return_date.'</td>
                        <td>'.$row->done_by.'</td>';
                    }
                ?>
            </tbody>
        </table>
    </div>
</div>
    
    <script src="../js/jquery.js"></script>
    <script src="../js/mainui.js"></script>
    <script src="../js/bootstrap.min.js"></script>
</body>
</html>