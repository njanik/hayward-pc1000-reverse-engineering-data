<?php

//En cours de construction.......!!!!!!


$handle = fopen("no-touch.csv", "r");
$previousTime = 0;
$lineNumber = 0;
$allDurations = [];

while (($line = fgets($handle)) !== false) {
  if($lineNumber++ === 5000000) {
    break;
  }
  $data = explode(',', $line);
  if($data[0] === 'Time[s]') {
    continue;
  }
  $timestamp = (int) round($data[0] * 1000);
  $duration = (int) round(($data[0] - $previousTime) * 1000);
  $previousTime = $data[0];

  if(!isset($allDurations[$duration])) {
    $allDurations[$duration] = 0;
  }
  $allDurations[$duration]++;

  if($duration === 0) {
    continue;
  }
  $vcc = trim($data[1]);
  if(!$vcc) { //si on vient de passer a 5v, on garde (car les les etats binaire 0 (3ms a 5v) et 1 (1ms a 5v) ne sont représenté que par le 5v)

    if($duration > 149 && $duration < 155) {
      echo "\n";
    }
    if($duration < 3) {
      $bit = 1;
    } else if($duration < 4) {
      $bit = '.';
    }
  }
  //echo $duration."\n";continue;
  if(!$vcc) {
    //echo $timestamp.' > '.$duration." (".$bit.") [".$vcc."]\n";
    echo $bit;
  } else {
    //si on est la, c'est qu'on etait à 0v
  }
  //echo $bit."\n";
}

asort($allDurations);
echo 'Sort by duration // [duration] => occurence'."\n";
print_r($allDurations);
echo "\n";
ksort($allDurations);
echo 'Sort by occurence // [duration] => occurence'."\n";
print_r($allDurations);
