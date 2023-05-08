# check if _BandWidth_ and _ErrorRate_ argumets are provided
if { $argc != 3 } {
	puts "This script requires three argumets to be inputed."
	puts "Command format : ns sim_script.tcl #BandWidth #PackSize #ErrorRate "
	puts "Please try again."
	exit 0
}

# Opttions

set opt(chan)	Channel/WirelessChannel
set opt(prop)	Propagation/TwoRayGround
set opt(netif)	Phy/WirelessPhy
set opt(mac)	Mac/802_11
set opt(ifq)	Queue/DropTail/PriQueue
set opt(ll)		LL
set opt(ant)        Antenna/OmniAntenna
set opt(x)		800   ;# X dimension of the topography
set opt(y)		800   ;# Y dimension of the topography
set opt(ifqlen)	50	      ;# max packet in ifq
set opt(tr)		sim_tr.tr    ;# trace file
set opt(nam)            sim_nam.nam   ;# nam trace file
set opt(adhocRouting)   AODV
set opt(nn)             9             ;# how many nodes are simulated
set opt(stop)		100.0		;# simulation time


set opt(bndWidth) [lindex $argv 0]
set opt(pckSize) [lindex $argv 1]			;# it's usually 512 bytes
set errRate [lindex $argv 2]

set opt(winSize) 20


# =====================================================================
# Other default settings

Agent/TCPSink set sport_	0
Agent/TCPSink set dport_	0

Agent/TCP set sport_		0
Agent/TCP set dport_		0
Agent/TCP set packetSize_	$opt(pckSize)

Queue/DropTail/PriQueue set Prefer_Routing_Protocols    1

# unity gain, omni-directional antennas
# set up the antennas to be centered in the node and 1.5 meters above it
Antenna/OmniAntenna set X_ 0
Antenna/OmniAntenna set Y_ 0
Antenna/OmniAntenna set Z_ 1.5
Antenna/OmniAntenna set Gt_ 1.0
Antenna/OmniAntenna set Gr_ 1.0

# Initialize the SharedMedia interface with parameters to make
# it work like the 914MHz Lucent WaveLAN DSSS radio interface
Phy/WirelessPhy set CPThresh_ 10.0
Phy/WirelessPhy set CSThresh_ 1.559e-11
Phy/WirelessPhy set RXThresh_ 3.652e-10
Phy/WirelessPhy set Rb_ 2*1e6
Phy/WirelessPhy set Pt_ 0.2818
Phy/WirelessPhy set freq_ 914e+6 
Phy/WirelessPhy set L_ 1.0


# ======================================================================
# Main Program
# ======================================================================


#
# Initialize Global Variables
#

# create simulator instance

set ns_		[new Simulator]

# set wireless channel, radio-model and topography objects

#set wprop	[new $opt(prop)]
# set wchan	[new $opt(chan)]						;##############################also line 132###################################
set wtopo	[new Topography]

# create trace object for ns and nam

set tracefd	[open $opt(tr) w]
set namtrace    [open $opt(nam) w]

$ns_ trace-all $tracefd
$ns_ eventtrace-all
$ns_ namtrace-all-wireless $namtrace $opt(x) $opt(y)

# define topology

$wtopo load_flatgrid $opt(x) $opt(y)
#$wprop topography $wtopo

#
# Create God
#
set god_ [create-god $opt(nn)]

#
# Define ErrorModel
#
proc UniformErrorModel {} {     
	global errRate
	set err [new ErrorModel]
	$err unit packet
	$err set rate_ $errRate
	$err ranvar [new RandomVariable/Uniform]
	return $err
}

#
# define how node should be created
#

#global node setting

$ns_ node-config 	-adhocRouting $opt(adhocRouting) \
									-llType $opt(ll) \
									-macType $opt(mac) \
									-ifqType $opt(ifq) \
									-ifqLen $opt(ifqlen) \
									-antType $opt(ant) \
									-propType $opt(prop) \
									-phyType $opt(netif) \
									-channelType $opt(chan) \
									-topoInstance $wtopo \
									-agentTrace ON \
                 	-routerTrace ON \
                 	-macTrace OFF \
								 	-movementTrace OFF \
									-incomingErrProc UniformErrorModel \
									-OutgoingErrProc UniformErrorModel

# set network bandwidth
$opt(mac) set basicRate_ 0
$opt(mac) set dataRate_ 0
$opt(mac) set bandwidth_ $opt(bndWidth)Mb

#
#  Create the specified number of nodes [$opt(nn)] and "attach" them
#  to the channel. 

for {set i 0} {$i < $opt(nn) } {incr i} {
	set node_($i) [$ns_ node]	
	$node_($i) random-motion 0		;# disable random motion
	# $node_($i) color black
}

#
#	define postions and labels of nodes
#
puts "Loading connection pattern..."

set scale 1

$node_(0) set X_ [expr $scale * 200.0]
$node_(0) set Y_ [expr $scale * 600.0]
$node_(0) set Z_ 0.0
$node_(0) label "A" 

$node_(1) set X_ [expr $scale * 75.0]
$node_(1) set Y_ [expr $scale * 400.0]
$node_(1) set Z_ 0.0
$node_(1) label "B"

$node_(2) set X_ [expr $scale * 400.0]
$node_(2) set Y_ [expr $scale * 500.0]
$node_(2) set Z_ 0.0
$node_(2) label "C"

$node_(3) set X_ [expr $scale * 200.0]
$node_(3) set Y_ [expr $scale * 200.0]
$node_(3) set Z_ 0.0
$node_(3) label "D"

$node_(4) set X_ [expr $scale * 400.0]
$node_(4) set Y_ [expr $scale * 300.0]
$node_(4) set Z_ 0.0
$node_(4) label "E" 

$node_(5) set X_ [expr $scale * 570.0]
$node_(5) set Y_ [expr $scale * 270.0]
$node_(5) set Z_ 0.0
$node_(5) label "F"  

$node_(6) set X_ [expr $scale * 570.0]
$node_(6) set Y_ [expr $scale * 570.0]
$node_(6) set Z_ 0.0
$node_(6) label "G" 

$node_(7) set X_ [expr $scale * 750.0]
$node_(7) set Y_ [expr $scale * 600.0]
$node_(7) set Z_ 0.0
$node_(7) label "H"

$node_(8) set X_ [expr $scale * 750.0]
$node_(8) set Y_ [expr $scale * 200.0]
$node_(8) set Z_ 0.0
$node_(8) label "L"

# $node_(0) set X_ [expr $scale * 2]
# $node_(0) set Y_ [expr $scale * 5]
# $node_(0) set Z_ 0.0
# $node_(0) label "A" 

# $node_(1) set X_ [expr $scale * 1]
# $node_(1) set Y_ [expr $scale * 3]
# $node_(1) set Z_ 0.0
# $node_(1) label "B"

# $node_(2) set X_ [expr $scale * 3]
# $node_(2) set Y_ [expr $scale * 4]
# $node_(2) set Z_ 0.0
# $node_(2) label "C"

# $node_(3) set X_ [expr $scale * 2]
# $node_(3) set Y_ [expr $scale * 1]
# $node_(3) set Z_ 0.0
# $node_(3) label "D"

# $node_(4) set X_ [expr $scale * 3]
# $node_(4) set Y_ [expr $scale * 2]
# $node_(4) set Z_ 0.0
# $node_(4) label "E" 

# $node_(5) set X_ [expr $scale * 4]
# $node_(5) set Y_ [expr $scale * 2]
# $node_(5) set Z_ 0.0
# $node_(5) label "F"  

# $node_(6) set X_ [expr $scale * 4]
# $node_(6) set Y_ [expr $scale * 4]
# $node_(6) set Z_ 0.0
# $node_(6) label "G" 

# $node_(7) set X_ [expr $scale * 5 + 100]
# $node_(7) set Y_ [expr $scale * 4]
# $node_(7) set Z_ 0.0
# $node_(7) label "H"

# $node_(8) set X_ [expr $scale * 5 + 100]
# $node_(8) set Y_ [expr $scale * 2]
# $node_(8) set Z_ 0.0
# $node_(8) label "L"


# 
# Define traffic model
#
puts "Loading scenario file..."

#
# A sends data to H at time 2.0 and stops at 96.0
#
set tcp_(0) [$ns_ create-connection  TCP $node_(0) TCPSink $node_(7) 0]
$tcp_(0) set window_ $opt(winSize)
$tcp_(0) set packetSize_ $opt(pckSize)
set ftp_(0) [$tcp_(0) attach-source FTP]
$ns_ at 2 "$ftp_(0) start"
$ns_ at 96 "$ftp_(0) stop"
#
# A sends data to L at time 2.0 and stops at 96.0
#
set tcp_(1) [$ns_ create-connection  TCP $node_(0) TCPSink $node_(8) 0]
$tcp_(1) set window_  $opt(winSize)
$tcp_(1) set packetSize_ $opt(pckSize)
set ftp_(1) [$tcp_(1) attach-source FTP]
$ns_ at 2 "$ftp_(1) start"
$ns_ at 96 "$ftp_(1) stop"
#
# D sends data to H at time 2.0 and stops at 96.0
#
set tcp_(2) [$ns_ create-connection  TCP $node_(3) TCPSink $node_(7) 0]
$tcp_(2) set window_ $opt(winSize)
$tcp_(2) set packetSize_ $opt(pckSize)
set ftp_(2) [$tcp_(2) attach-source FTP]
$ns_ at 2 "$ftp_(2) start"
$ns_ at 96 "$ftp_(2) stop"
#
# D sends data to L at time 2.0 and stops at 96.0
#
set tcp_(3) [$ns_ create-connection  TCP $node_(3) TCPSink $node_(8) 0]
$tcp_(3) set window_ $opt(winSize)
$tcp_(3) set packetSize_ $opt(pckSize)
set ftp_(3) [$tcp_(3) attach-source FTP]
$ns_ at 2 "$ftp_(3) start"
$ns_ at 96 "$ftp_(3) stop"


# Define node initial position in nam

for {set i 0} {$i < $opt(nn)} {incr i} {
    $ns_ initial_node_pos $node_($i) 20
}

#
# Tell nodes when the simulation ends
#
for {set i 0} {$i < $opt(nn) } {incr i} {
    $ns_ at $opt(stop).000000001 "$node_($i) reset";
}

#
# finish procedure
#
proc finish {} {
	global ns_ tracefd namtrace opt
	
	$ns_ nam-end-wireless $opt(stop)
	$ns_ flush-trace
	close $tracefd
	close $namtrace
}

$ns_ at $opt(stop) "finish"
$ns_ at  $opt(stop).000000001 "puts \"NS EXITING...\" ; $ns_ halt"


puts "Starting Simulation..."
$ns_ run
