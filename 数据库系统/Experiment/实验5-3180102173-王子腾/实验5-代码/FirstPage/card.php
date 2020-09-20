<?php 
    $conn = new mysqli('localhost', 'root', 'wzt75276477', 'test', '3306');
    if ($conn->connect_error) {
        die("连接失败: " . $conn->connect_error);
    }
    
    $sql="select * from card";
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
            <a class="nav-link" href="return.php">Return</a>
            <a class="nav-link active" href="card.php">Cards</a>
        </nav>
    </div>

    <div class="row">
        <div class="col-md-4 order-md-1">
            <form class="form-signin " action="../SecondPage/Card.php" method="POST">
                <h1 class="h3 mb-3 text-light font-weight-normal">Card Infomation</h1>

                <label for="inputEmail" class="sr-only">cno</label>
                <input type="id" id="inputEmail" class="form-control" placeholder="Card Number" name="cno" required autofocus>

                <label for="inputPassword" class="sr-only">name</label>
                <input type="id" id="inputPassword" class="form-control" placeholder="Name" name="name" required autofocus>

                <label for="inputEmail" class="sr-only">department</label>
                <input type="id" id="inputEmail" class="form-control" placeholder="Department" name="dep" required autofocus>

                <label for="inputPassword" class="sr-only">type</label>
                <input type="id" id="inputPassword" class="form-control" placeholder="Type" name="type" required autofocus>

                <div class="input-group mb-3">
                <div class="input-group-prepend">
                    <label class="input-group-text" for="inputGroupSelect01">Options</label>
                </div>
                <select class="custom-select" name="opt" id="inputGroupSelect01">
                    <option selected value="1" >Append</option>
                    <option value="2">Delete</option>
                </select>
                </div>
                <button class="btn btn-lg btn-primary btn-block" type="submit">Submit</button>
            </form>
        </div>
    
        <div class="col-md-7 order-md-2 text-center">
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