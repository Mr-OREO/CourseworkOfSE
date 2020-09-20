<?php 
    $conn = new mysqli('localhost', 'root', 'wzt75276477', 'test', '3306');
    if ($conn->connect_error) {
        die("连接失败: " . $conn->connect_error);
    }
    
    $sql="select * from book";
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

    <!-- 首页 -->
    <nav class="navbar navbar-expand-lg fixed-top navbar-dark" style="background-color: #343a40;">
        <div>
            <a class="navbar-brand mr-auto mr-lg-0">Book Management System</a>
        </div>
    </nav>

    <div class="nav-scroller bg-white shadow-sm">
        <nav class="nav nav-underline">
            <a class="nav-link disabled" href="append.html">Append</a>
            <a class="nav-link active disabled" href="search.php">Search</a>
            <a class="nav-link disabled" href="borrow.php">Borrow</a>
            <a class="nav-link disabled" href="return.php">Return</a>
            <a class="nav-link disabled" href="card.php">Cards</a>
        </nav>
    </div>

    <!--查询界面-->
<div class="row">
    <div class="col-md-4 order-md-1">
        <form class="form-signin" action="../SecondPage/search_user.php" method="POST" novalidate>
            <h4 class="mb-3 text-light">Search By Limits</h4>
            <!-- category title -->
            <div class="row">
                <div class="col-md-6 mb-3">
                <label for="category" class="text-light">Category</label>
                <input type="text" class="form-control" id="category" name="cat" placeholder="" value="" required>
                </div>
                <div class="col-md-6 mb-3">
                <label for="title" class="text-light">Title</label>
                <input type="text" class="form-control" id="title" name="tit" placeholder="" value="" required>
                </div>
            </div>
    
            <!-- press author -->
            <div class="row">
                <div class="col-md-6 mb-3">
                <label for="press" class="text-light">Press</label>
                <input type="text" class="form-control" id="press" name="pre" placeholder="" value="" required>
                </div>
                <div class="col-md-6 mb-3">
                <label for="author" class="text-light">Author</label>
                <input type="text" class="form-control" id="author" name="aut" placeholder="" value="" required>
                </div>
            </div>

            <div class="row">
                <!-- price -->
                <div class="col-md-3 mb-3">
                <label for="pricel" class="text-light">Price</label>
                <input type="text" class="form-control" id="pricel" name="prl" placeholder="low" value="" required>
                </div>
                <div class="col-md-3 mb-3">
                <label for="priceh" class="text-dark">high</label>
                <input type="text" class="form-control" id="priceh" name="prh" placeholder="high" value="" required>
                </div>
                <!-- year -->
                <div class="col-md-3 mb-3">
                <label for="yearl" class="text-light">Year</label>
                <input type="text" class="form-control" id="yearl" name="yel" placeholder="low" value="" required>
                </div>
                <div class="col-md-3 mb-3">
                <label for="yearh" class="text-dark">high</label>
                <input type="text" class="form-control" id="yearh" name="yeh" placeholder="high" value="" required>
                </div>
            </div>

            <div class="row">
                <div class="col-md-12 mb-3">
                <label class="text-light">Order</label>
                <select class="custom-select" name="opt" id="inputGroupSelect01">
                    <option value="1" >bno</option>
                    <option value="2">category</option>
                    <option selected value="3">title</option>
                    <option value="4">press</option>
                    <option value="5">author</option>
                    <option value="6">price</option>
                    <option value="7">total</option>
                    <option value="8">stock</option>
                </select>
                </div>
            </div>

            <div class="container">
                <div class="row justify-content-md-center">
                    <button class="btn btn-primary btn-lg col-4">Submit</button>
                </div>
            </div>
        </form>
    </div>
  
    <div class="col-md-7 order-md-2">
        <table class="table text-light h5">
            <thead>
                <tr>
                <th scope="col">bno</th>
                <th scope="col">category</th>
                <th scope="col">title</th>
                <th scope="col">press</th>
                <th scope="col">year</th>
                <th scope="col">author</th>
                <th scope="col">price</th>
                <th scope="col">total</th>
                <th scope="col">stock</th>
                </tr>
            </thead>
            <tbody>
                <?php 
                    while($row=$result->fetch_object())
                    {
                        echo '
                        <tr>
                        <td>'.$row->bno.'</td>
                        <td>'.$row->category.'</td>
                        <td>'.$row->title.'</td>
                        <td>'.$row->press.'</td>
                        <td>'.$row->year.'</td>
                        <td>'.$row->author.'</td>
                        <td>'.$row->price.'</td>
                        <td>'.$row->total.'</td>
                        <td>'.$row->stock.'</td>
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