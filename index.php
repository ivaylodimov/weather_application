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

$conn->close();
?>

    <head>
        <meta http-equiv="cache-control" content="no-cache" />
        <meta http-equiv="refresh" content="30">
        <meta charset="utf-8">
        <meta name="viewport" content="initial-scale=1.0">
        <title>Weather Application</title>
        <link href="http://fonts.googleapis.com/css?family=Montserrat:400,700,inherit,400" rel="stylesheet" type="text/css">
        <link rel="stylesheet" href="css/standardize.css">
        <link rel="stylesheet" href="css/index.css">
        <script type="text/javascript" src="js/time.js"></script>
     </head>

    <body class="body page-index clearfix">
    <div class="container clearfix">
        <p id="temp" class="temperature"></p>
        <p id="temp_f" class="temperature_f"></p>
        <p id="temp_index_c" class="temp_index_c"></p>
        <img class="rainicon" src="images/Rainicon.svg">
        <div id="rain" class="rainmm"></div>
        <img class="droplet" src="images/Droplet.svg">
        <p id="hum" class="humidity"></p>
        <div id="presure" class="pressure"></div>
        <div id="dusting" class="pm"> </div>
        <img class="sunicon" src="images/Sun.svg">
        <div id="sun" class="sun"></div>
    </div>
   <script>
         var hum = <?php echo $row["hum"]; ?> ;
         var rain = <?php echo $row["rain"]; ?> ;
         var presure = <?php echo $row["presure"]; ?> ;
         var dusting = <?php echo $row["dusting"]; ?> ;
         var sun = <?php echo $row["sun"]; ?> ;
         var temperature = <?php echo $row["temperature"]; ?> ;
         var temperature_f = <?php echo $row["temperature_f"]; ?> ;
         var temp_index_c = <?php echo $row["temp_index_c"]; ?> ;
         var temp_index_f = <?php echo $row["temp_index_f"]; ?> ;
         document.getElementById("temp").innerHTML = temperature + "&deg;" + 'C';
         document.getElementById("temp_f").innerHTML = temperature_f + "&deg;" +'F';
         document.getElementById("rain").innerHTML = rain + 'mm';
         document.getElementById("hum").innerHTML = hum + '%';
         document.getElementById("temp_index_c").innerHTML = 'Усеща се като: ' + temp_index_c + "&deg;" + 'C' + ' ' + temp_index_f + "&deg;" + 'F';
         document.getElementById("presure").innerHTML ='Атмосферно налягане:' + ' ' + presure + 'hPA';
         document.getElementById("dusting").innerHTML = 'Прахови частици:' + ' ' + dusting + 'µg/m3';
         document.getElementById("sun").innerHTML = 'Осветеност:' + ' ' + sun + ' ' + "LUX";
    </script>

    <p id="statistics" class="statistics"> <a href="statistics.php">Статистика на измерванията</a></p>

        <script>
          var a = "<?php echo $row["timestamp"]; ?>";
        </script>

    <div class="info_bg">
        <svg height="30" width="500">
            <text x="25" y="15" fill="white">2018 IRD Ивайло Димов ТУ-Габрово</text>
        </svg>
        <p id="date"></p>
        <script>
             document.getElementById("date").innerHTML = Date();
        </script>
    </div>
  </body>
</html>
