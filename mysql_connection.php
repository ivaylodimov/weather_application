<?php
$servername = ''; //адрес на MySQL сървър
$username = ''; //потребителско име
$password = 'dB7!qW5%'; // парола
$dbname = 'sql2256268'; //име на БД

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
 ?>
