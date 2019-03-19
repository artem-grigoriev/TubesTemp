<html>
<head></head>

<?php

$file = '/home/pi/tt_dump.sql';

if(!file_exists($file)){ // file does not exist
    die('file not found');
} else {
    header("Cache-Control: public");
    header("Content-Description: File Transfer");
    header("Content-Disposition: attachment; filename=$file");
    header("Content-Type: application/zip");
    header("Content-Transfer-Encoding: binary");

    // read the file from disk
    readfile($file);
}?>
<body><p>Dump have been downloaded</p></body>
</html>