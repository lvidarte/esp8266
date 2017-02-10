<?PHP

const LOG_FILE = "server.log";
const FIRMWARE_DIR = "../firmware";


$firmwares = scandir(FIRMWARE_DIR);

$db = [
    "5C:CF:7F:C0:3E:87" => basename(end($firmwares), FIRMWARE_DIR),
];


function logging($message)
{
    if (is_array($message)) {
        $message = print_r($message, true);
    }
    error_log($message . "\n", 3, LOG_FILE);
}


function check_header($name, $value = false)
{
    if (!isset($_SERVER[$name])) {
        return false;
    }
    if ($value && $_SERVER[$name] != $value) {
        return false;
    }
    return true;
}

function sendFile($path)
{
	error_log("Sending file " . $path);
    header($_SERVER["SERVER_PROTOCOL"].' 200 OK', true, 200);
    header('Content-Type: application/octet-stream', true);
    header('Content-Disposition: attachment; filename='.basename($path));
    header('Content-Length: '.filesize($path), true);
    header('x-MD5: '.md5_file($path), true);
    readfile($path);
}




logging($_SERVER);

header('Content-type: text/plain; charset=utf8', true);


if ( ! check_header('HTTP_USER_AGENT', 'ESP8266-http-Update')) {
    header($_SERVER["SERVER_PROTOCOL"].' 403 Forbidden', true, 403);
    echo "only for ESP8266 updater!\n";
    exit();
}

if (
    ! check_header('HTTP_X_ESP8266_STA_MAC') ||
    ! check_header('HTTP_X_ESP8266_AP_MAC') ||
    ! check_header('HTTP_X_ESP8266_FREE_SPACE') ||
    ! check_header('HTTP_X_ESP8266_SKETCH_SIZE') ||
    ! check_header('HTTP_X_ESP8266_CHIP_SIZE') ||
    ! check_header('HTTP_X_ESP8266_SDK_VERSION') ||
    ! check_header('HTTP_X_ESP8266_VERSION')
) {
    header($_SERVER["SERVER_PROTOCOL"].' 403 Forbidden', true, 403);
    echo "only for ESP8266 updater! (header)\n";
    exit();
}

if (isset($db[$_SERVER['HTTP_X_ESP8266_STA_MAC']])) {
    if ($db[$_SERVER['HTTP_X_ESP8266_STA_MAC']] != $_SERVER['HTTP_X_ESP8266_VERSION']) {
        $file = "./bin/" . $db[$_SERVER['HTTP_X_ESP8266_STA_MAC']] . ".bin";
        logging("Sending file " . $file);
        sendFile($file);
    } else {
        header($_SERVER["SERVER_PROTOCOL"].' 304 Not Modified', true, 304);
    }
    exit();
}

header($_SERVER["SERVER_PROTOCOL"].' 500 no version for ESP MAC', true, 500);
