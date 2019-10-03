set ns [new Simulator]


set nt [open simulate.nam w]
$ns namtrace-all $nt

set tr [open udp-120.tr w]
$ns trace-all $tr

proc finish {} {
	global ns nt tr
	$ns flush-trace
	close $nt
	close $tr  
	exec nam simulate.nam &
	exit 0
}

set S [$ns node]
set R [$ns node]
set D [$ns node]

$ns duplex-link $S $R 1Mb 50ms SFQ
$ns duplex-link $R $D 100Kb 5ms SFQ

$ns queue-limit $R $D 10

$ns duplex-link-op $S $R orient right
$ns duplex-link-op $R $D orient right

$ns duplex-link-op $S $R queuePos 1.0
$ns duplex-link-op $R $D queuePos 1.0

set udp [new Agent/UDP]
$ns attach-agent $S $udp

set null [new Agent/Null]
$ns attach-agent $D $null
$ns connect $udp $null

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set packet_size_ 1000
$cbr set rate_ 120kb
$cbr set random_ false

$ns at 0.1 "$cbr start"
$ns at 10.0 "$cbr stop"

$ns at 10.1 "finish"

$ns run