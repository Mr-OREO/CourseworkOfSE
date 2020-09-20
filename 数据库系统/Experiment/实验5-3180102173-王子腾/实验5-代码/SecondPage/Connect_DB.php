<?php 
$servername = "localhost";
$username = "root";
$password = "wzt75276477";

//connection
$conn = new mysqli('localhost', 'root', 'wzt75276477', 'test', '3306');
if ($conn->connect_error) {
    die("连接失败: " . $conn->connect_error);
}

?>

