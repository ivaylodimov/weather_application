<!DOCTYPE HTML>
<html>
    <?php
include 'mysql_connection.php';
$sql = "SELECT * FROM weather_station ORDER BY timestamp DESC LIMIT 1";
$result = $conn->query($sql);
$row = $result->fetch_assoc() ;

@mysqli_select_db($dbname);

  @mysqli_set_charset($conn, "utf8");
  $query='SELECT * FROM weather_station ';
  $result1=@mysqli_query($conn, $query);
  $a='';
  if ($result1) {

      $a='<table border=2>';
      $a.='<tr>
              <th>Дата</th>
              <th>Температура °C</th>
              <th>Температура °F</th>
              <th>Влажност</th>
              <th>Топлинен индекс °C</th>
              <th>Топлинен индекс °F</th>
              <th>Количество валежи</th>
              <th>Атмосферно налягане</th>
              <th>Прахови частици</th>
              <th>Осветеност</th>
            </tr>';
          while ($row1=@mysqli_fetch_row($result1)) {
            $a.='<tr><td>'.$row1[0].'</td><td>'.$row1[1].'</td><td>'.$row1[2].'</td><td>'.$row1[3].'</td><td>'.$row1[4].'</td><td>'.$row1[5].'</td><td>'.$row1[6].'</td><td>'.$row1[7].'</td><td>'.$row1[8].'</td><td>'.$row1[9].'</td></tr>';
          }
      $a.='</table>';

  } else {
      $a="Не е възможно изпълнението на подадената заявка!";
  }

  echo $a;

$conn->close();
?>

    <head>
        <meta http-equiv="cache-control" content="no-cache" />
        <meta http-equiv="refresh" content="30">
        <meta charset="utf-8">
        <meta name="viewport" content="initial-scale=1.0">
        <title>Measurement statistics</title>
        <link href="http://fonts.googleapis.com/css?family=Montserrat:400,700,inherit,400" rel="stylesheet" type="text/css">
        <link rel="stylesheet" href="css/standardize.css">
        <link rel="stylesheet" href="css/index.css">
        <script type="text/javascript" src="js/time.js"></script>
     </head>
<p id="statistics" class="statistics"> <a href="index.php">Обратно към началната страница</a></p>
        <script>
          var a = "<?php echo $row["timestamp"]; ?>";
        </script>

    <div class="info_bg">
        <svg height="30" width="500">
            <text x="25" y="15" fill="white">© 1999-2018 IRD Всички права запазени</text>
        </svg>
        <p id="date"></p>
        <script>
             document.getElementById("date").innerHTML = Date();
        </script>
    </div>
  </body>
</html>
