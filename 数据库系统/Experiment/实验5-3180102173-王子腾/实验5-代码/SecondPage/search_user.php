<?php 
    $conn = new mysqli('localhost', 'root', 'wzt75276477', 'test', '3306');
    if ($conn->connect_error) {
        die("连接失败: " . $conn->connect_error);
    }
    
    $cat = $_POST['cat'];
    $tit = $_POST['tit'];
    $pre = $_POST['pre'];
    $aut = $_POST['aut'];
    $prl = $_POST['prl'];
    $prh = $_POST['prh'];
    $yel = $_POST['yel'];
    $yeh = $_POST['yeh'];
    $opt = $_POST['opt'];

    $sql = "select * from book where";
    
    $isnull = true;
    if($cat != ""){
        $sql = $sql." category='".$cat."' ";
        $isnull = false;
    }
    if($tit != ""){
        if($isnull){
            $sql = $sql." title='".$tit."' ";
        }
        else{
            $sql = $sql."and title='".$tit."' ";
        }
        $isnull = false;
    }
    if($pre != ""){
        if($isnull){
            $sql = $sql." press='".$pre."' ";
        }
        else{
            $sql = $sql."and press='".$pre."' ";
        }
        $isnull = false;
    }
    if($aut != ""){
        if($isnull){
            $sql = $sql." author='".$aut."' ";
        }
        else{
            $sql = $sql."and author='".$aut."' ";
        }
        $isnull = false;
    }
    if($prl != "" || $prh != ""){
        if($prl == "")  $prl = "0";
        if($prh == "")  $prh = "9999";
        if($isnull){
            $sql = $sql." price between ".$prl." and ".$prh." ";
        }
        else{
            $sql = $sql."and price between ".$prl." and ".$prh." ";
        }
        $isnull = false;
    }
    if($yel != "" || $yeh != ""){
        if($yel == "")  $yel = "0";
        if($yeh == "")  $yeh = "9999";
        if($isnull){
            $sql = $sql." year between ".$yel." and ".$yeh." ";
        }
        else{
            $sql = $sql."and year between ".$yel." and ".$yeh." ";
        }
        $isnull = false;
    }
    if ($isnull){
		$sql = "select * from book ";
    }
    switch($opt)
    {
        case 1:
            $sql=$sql."order by bno";break;
        case 2:
            $sql=$sql."order by category";break;
        case 3:
            $sql=$sql."order by title";break;
        case 4:
            $sql=$sql."order by press";break;
        case 5:
            $sql=$sql."order by author";break;
        case 6:
            $sql=$sql."order by price";break;
        case 7:
            $sql=$sql."order by total";break;
        case 8:
            $sql=$sql."order by stock";break;
    }

    $result = $conn->query($sql);
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
            <a class="nav-link disabled" href="../FirstPage/append.html">Append</a>
            <a class="nav-link active disabled" href="../FirstPage/search.php">Search</a>
            <a class="nav-link disabled" href="../FirstPage/borrow.php">Borrow</a>
            <a class="nav-link disabled" href="../FirstPage/return.php">Return</a>
            <a class="nav-link disabled" href="../FirstPage/card.php">Cards</a>
        </nav>
    </div>

    <!--查询界面-->
    <div class = "row">
    <div class="col-md-4 order-md-1">
        <form class="form-signin">
            <h4 class="mb-3 text-light">Search By Limits</h4>
            <!-- category title -->
            <div class="row">
                <div class="col-md-6 mb-3">
                <label for="category" class="text-light">Category</label>
                <input type="text" class="form-control disabled" id="category" name="cat" placeholder="<?php if($cat!="")echo "$cat";else echo "all" ?>" value="" required>
                </div>
                <div class="col-md-6 mb-3">
                <label for="title" class="text-light">Title</label>
                <input type="text" class="form-control disabled" id="title" name="tit" placeholder="<?php if($tit!="")echo "$tit";else echo "all" ?>" value="" required>
                </div>
            </div>
    
            <!-- press author -->
            <div class="row">
                <div class="col-md-6 mb-3">
                <label for="press" class="text-light">Press</label>
                <input type="text" class="form-control disabled" id="press" name="pre" placeholder="<?php if($pre!="")echo "$pre";else echo "all" ?>" value="" required>
                </div>
                <div class="col-md-6 mb-3">
                <label for="author" class="text-light">Author</label>
                <input type="text" class="form-control disabled" id="author" name="aut" placeholder="<?php if($aut!="")echo "$aut";else echo "all" ?>" value="" required>
                </div>
            </div>

            <div class="row">
                <!-- price -->
                <div class="col-md-3 mb-3">
                <label for="pricel" class="text-light">Price</label>
                <input type="text" class="form-control disabled" id="pricel" name="prl" placeholder="<?php if($prl!="")echo "$prl";else echo "0" ?>" value="" required>
                </div>
                <div class="col-md-3 mb-3">
                <label for="priceh" class="text-dark">high</label>
                <input type="text" class="form-control disabled" id="priceh" name="prh" placeholder="<?php if($prh!="")echo "$prh";else echo "9999" ?>" value="" required>
                </div>
                <!-- year -->
                <div class="col-md-3 mb-3">
                <label for="yearl" class="text-light">Year</label>
                <input type="text" class="form-control disabled" id="yearl" name="yel" placeholder="<?php if($yel!="")echo "$yel";else echo "0" ?>" value="" required>
                </div>
                <div class="col-md-3 mb-3">
                <label for="yearh" class="text-dark">high</label>
                <input type="text" class="form-control disabled" id="yearh" name="yeh" placeholder="<?php if($yeh!="")echo "$yeh";else echo "9999" ?>" value="" required>
                </div>
            </div>

            <div class="container">
                <div class="row justify-content-md-center">
                    <a class="btn btn-info btn-lg col-4" href="../FirstPage/search_user.php">Try Again</a>
                </div>
            </div>
        </form>
    </div>

    <div class="col-md-7 order-md-2 text-center">
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