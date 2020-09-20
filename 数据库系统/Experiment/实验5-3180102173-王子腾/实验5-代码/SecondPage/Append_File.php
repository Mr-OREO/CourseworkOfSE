<?php 
    $conn = new mysqli('localhost', 'root', 'wzt75276477', 'test', '3306');
    if ($conn->connect_error) {
        die("连接失败: " . $conn->connect_error);
    }
    $ERROR=0;

    // print_r($_FILES);
    
    // 获取文件名
    $filename="1.xls";
    // 检查文件
    if(!file_exists($filename))
    {
        $ERROR=1;
    }

    require_once "../PHPExcel/IOFactory.php";
    require_once "../PHPExcel/PHPExcel.php";
    $phpexce=PHPExcel_IOFactory::load($filename);
    $phpexce->setActiveSheetIndex(0);

    $row=$phpexce->getActiveSheet()->getHighestRow();
    $col=$phpexce->getActiveSheet()->getHighestColumn();

    for($i=2, $j='A'; $i<=$row; $i++)
    {
        $j='A';
        $bno=$phpexce->getActiveSheet()->getCell($j.$i)->getValue();
        $j='B';
        $cat=$phpexce->getActiveSheet()->getCell($j.$i)->getValue();
        $j='C';
        $tit=$phpexce->getActiveSheet()->getCell($j.$i)->getValue();
        $j='D';
        $pre=$phpexce->getActiveSheet()->getCell($j.$i)->getValue();
        $j='E';
        $yea=$phpexce->getActiveSheet()->getCell($j.$i)->getValue();
        $j='F';
        $aut=$phpexce->getActiveSheet()->getCell($j.$i)->getValue();
        $j='G';
        $pri=$phpexce->getActiveSheet()->getCell($j.$i)->getValue();
        $j='H';
        $tot=$phpexce->getActiveSheet()->getCell($j.$i)->getValue();
        $j='I';
        $sto=$phpexce->getActiveSheet()->getCell($j.$i)->getValue();

        $sql="select * from book where bno='".$bno."'";
        $result=$conn->query($sql);

        if($ro=$result->fetch_object())
        {
            $ro->total+=$tot;
            $ro->stock+=$sto;
        }
        else
        {
            $sql = "insert into book values('".$bno."','".$cat."','".$tit."','".$pre."',".$yea.",'".$aut."',".$pri.",".$tot.",".$sto.")";
            $result = $conn->query($sql);
            if(!$result)
            {
                $ERROR=2;
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
            <a class="nav-link active" href="../FirstPage/append.html">Append</a>
            <a class="nav-link" href="../FirstPage/search.php">Search</a>
            <a class="nav-link" href="../FirstPage/borrow.php">Borrow</a>
            <a class="nav-link" href="../FirstPage/return.php">Return</a>
            <a class="nav-link" href="../FirstPage/card.php">Cards</a>
        </nav>
    </div>

<!-- feed back -->
    <div>
        <?php 
            if($ERROR==1){
                echo  '<form class="form-signin">
                <h1 class="h3 mb-3 text-light font-weight-normal">ERROR</h1>
                <div class="alert alert-danger" role="alert">"File Uploaded Unsuccessfully"</div>
                <a class="btn btn-lg btn-dark btn-block" href="../FirstPage/append.html">Back</a>
                </form>';
            }
            else if($ERROR==2){
                echo  '<form class="form-signin">
                <h1 class="h3 mb-3 text-light font-weight-normal">ERROR</h1>
                <div class="alert alert-danger" role="alert">"MySQL ERROR"</div>
                <a class="btn btn-lg btn-primary btn-block" href="../FirstPage/append.html">Back</a>
                </form>';
            }
            else{
                echo  '<form class="form-signin">
                <h1 class="h3 mb-3 text-light font-weight-normal">Success</h1>
                <div class="alert alert-success" role="alert">"You\'ve Inserted a List of Books"</div>
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