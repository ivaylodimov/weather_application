<?php
$servername = 'sql2.freemysqlhosting.net';
$username = 'sql2256268';
$password = 'dB7!qW5%';
$dbname = 'sql2256268';

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
 ?>
