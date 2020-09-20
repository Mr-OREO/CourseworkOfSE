<?php 
    $conn = new mysqli('localhost', 'root', 'wzt75276477', 'test', '3306');
    if ($conn->connect_error) {
        die("连接失败: " . $conn->connect_error);
    }
    
    $cno = $_POST['cno'];
    $nam = $_POST['name'];
    $dep = $_POST['dep'];
    $typ = $_POST['type'];
    $opt = $_POST['opt'];
    $ERROR = 0;

    if($opt=='1')// Append
    {
        $sql="select * from card where cno='".$cno."'";
        $result=$conn->query($sql);
        $row=$result->fetch_array();
        if($row)
        {
            $ERROR = 1;// Duptlicate
        }
        else{
            $sql="insert into card values('".$cno."','".$nam."','".$dep."','".$typ."')";
            $result=$conn->query($sql);
        }
    }
    else        // Delete
    {
        $sql="select * from card where cno='".$cno."'";
        $result=$conn->query($sql);
        $row=$result->fetch_array();
        if(!$row)
        {
            $ERROR = 2;// NonExist
        }
        else{
            $sql="select * from borrow where cno='".$cno."' and return_date is null";
            $result=$conn->query($sql);
            if($result)
            {
                $ERROR = 3; // Haven't return all books
            }
            else
            {
                $sql="delete from card where cno='".$cno."'";
                $result=$conn->query($sql);
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
            <a class="nav-link" href="../FirstPage/borrow.php">Borrow</a>
            <a class="nav-link" href="../FirstPage/return.php">Return</a>
            <a class="nav-link active" href="../FirstPage/card.php">Cards</a>
        </nav>
    </div>

    <div class="row">
        <div class="col-md-4 order-md-1">
            <form class="form-signin ">
                <h1 class="h3 mb-3 text-light font-weight-normal">Card Infomation</h1>

                <?php 
                    if($ERROR==1)
                    {
                        echo  '<div class="alert alert-danger" role="alert">"The Card Already Exists"</div>';
                    }
                    else if($ERROR==2){
                        echo  '<div class="alert alert-danger" role="alert">"The Card is NonExistent"</div>';
                    }
                    else if($ERROR==3){
                        echo  '<div class="alert alert-danger" role="alert">"Unreturned Book"</div>';
                    }
                    else if($opt==1){
                        echo  '<div class="alert alert-success" role="alert">"Append Successfully"</div>';
                    }
                    else{
                        echo  '<div class="alert alert-success" role="alert">"Delete Successfully"</div>';
                    }
                
                ?>

                <a class="btn btn-lg btn-primary btn-block" href="../FirstPage/card.php" type="submit">Back</a>
            </form>
        </div>
    
        <div class="col-md-8 order-md-2 text-center">
            <table class="table text-light h5">
            <thead>
                    <tr>
                    <th scope="col">cno</th>
                    <th scope="col">name</th>
                    <th scope="col">department</th>
                    <th scope="col">type</th>
                    </tr>
                </thead>
                <tbody>
                    <?php 
                        $sql="select * from card";
                        $result=$conn->query($sql);
                        while($row=$result->fetch_object())
                        {
                            echo '
                            <tr>
                            <td scope="col">'.$row->cno.'</td>
                            <td scope="col">'.$row->name.'</td>
                            <td scope="col">'.$row->department.'</td>
                            <td scope="col">'.$row->type.'</td>
                            </tr>';
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