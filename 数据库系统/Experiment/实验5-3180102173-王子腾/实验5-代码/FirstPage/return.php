<?php 
    $conn = new mysqli('localhost', 'root', 'wzt75276477', 'test', '3306');
    if ($conn->connect_error) {
        die("连接失败: " . $conn->connect_error);
    }
    
    $sql="select * from borrow";
    $result=$conn->query($sql);

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
            <a class="nav-link" href="append.html">Append</a>
            <a class="nav-link" href="search.php">Search</a>
            <a class="nav-link" href="borrow.php">Borrow</a>
            <a class="nav-link active" href="return.php">Return</a>
            <a class="nav-link" href="card.php">Cards</a>
        </nav>
    </div>

    <div class="row">
        <div class="col-md-4 order-md-1">
            <form class="form-signin " action="../SecondPage/Return.php" method="POST">
                <h1 class="h3 mb-3 text-light font-weight-normal">Infomation</h1>
                <label for="inputEmail" class="sr-only">CNO</label>
                <input type="id" id="inputEmail" class="form-control" placeholder="Card Number" name="cno" required autofocus>
                <label for="inputPassword" class="sr-only">BNO</label>
                <input type="id" id="inputPassword" class="form-control" placeholder="Book Number" name="bno" required autofocus>
                </label>
                <button class="btn btn-lg btn-primary btn-block" type="submit">Return</button>
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
                        while($row=$result->fetch_object())
                        {
                            echo '
                            <tr>
                            <td scope="col">'.$row->cno.'</td>
                            <td scope="col">'.$row->bno.'</td>
                            <td scope="col">'.$row->borrow_date.'</td>
                            <td scope="col">'.$row->return_date.'</td>
                            <td scope="col">'.$row->done_by.'</td>
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