set ns [new Simulator]

$ns color 1 Green
$ns color 2 Red

set nt [open simulate.nam w]
$ns namtrace-all $nt

set tr [open simulate.tr w]
$ns trace-all $tr

proc finish {} {
	global ns nt tr
	$ns flush-trace
	close $nt
	close $tr
	exec nam simulate.nam &
	exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns duplex-link $n0 $n1 2Mb 20ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail

$ns make-lan "$n0 $n1 $n2 $n3" 100Mb 300ms LL Queue/DropTail Mac/802_3


$ns queue-limit $n0 $n1 10
$ns queue-limit $n2 $n3 10

$ns duplex-link-op $n0 $n1 orient right-down
$ns duplex-link-op $n2 $n3 orient right-down
# $ns duplex-link-op $n0 $n2 orient down
# $ns duplex-link-op $n1 $n3 orient down

$ns duplex-link-op $n0 $n1 queuePos 0.5
$ns duplex-link-op $n2 $n3 queuePos 0.5

set tcp1 [new Agent/TCP]
$tcp1 set class_ 1
$ns attach-agent $n0 $tcp1

set sink1 [new Agent/TCPSink]
$ns attach-agent $n1 $sink1
$ns connect $tcp1 $sink1
$tcp1 set fid_ 1

set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ftp1 set type_ FTP

set tcp2 [new Agent/TCP]
$tcp2 set class_ 1
$ns attach-agent $n2 $tcp2

set sink2 [new Agent/TCPSink]
$ns attach-agent $n3 $sink2
$ns connect $tcp2 $sink2
$tcp2 set fid_ 2

set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
$ftp2 set type_ FTP

$ns at 0.1 "$ftp1 start"
$ns at 0.1 "$ftp2 start"
$ns at 4.5 "$ftp2 stop"
$ns at 4.5 "$ftp1 stop"

$ns at 5.0 "finish"

$ns run