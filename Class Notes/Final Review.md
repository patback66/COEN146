# COEN 146 Computer Networks

    - NOTHING BEFORE CHAPTER 3
    - Congestion Control

## TCP

    - change how fast it's speeding up, etc.
    - how fast (on average) you're sending data
    - max rate of transmission
    - TCP Segments -> chunks of data

## Chapter 3

    3.3.3 Most Important
        - Forwarding and routing table
        - Link-State Routing (OSPF)
            - Every node says who it can reach, along with cost
            - Only what you know firsthand
            - Share with everybody how you can reach your neighbors - build a map of firsthand knowledge
        - Flooding - must be reliable
            - This is how you share your connection information
            - Link-State packet
                - ID of the node
                - List of directly connected neighbors, with cost
                - sequence number
                - time to live for the packet
                - a subnet
                - the link state packets for the subnet
                - ex: |network (source/dest IP)| data|
                - use subaddresses to indicate where the packet will go
                  - be an apartment complex rather than a house
                  - 127 is a class A
            - Forward the packets so that everybody gets it, but not who gave it to you
            - Remove old info ASAP, get new info out ASAP
            - When to send packets? Only when necessary otherwise high overhead
        - Take shortest available path based on most up to date info
    3.3.4 Most important
        - Metrics
            - Bandwidth
            - Latency
            - Delay
    3.4.4 Strongly recommended
      - Implementation
    3.3,3.4 general awareness

## Chapter 4

    Routing algorithms
    4.1.1 bare minimum
        - Subdomains
        - Hierarchical routing
        - Route from source to backbone, backbone path, backbone to destination
        - Virtual link
    4.1.2 recommended
        - Distance vector like algorithm
        - Routing between domains
        - BGP - border gateway protocol
        - Local traffic and transit traffic
    4.1 overall, but 4.1.1 is the focus
    4.1.3 recommended

## Chapter 5

    5.1
        - UDP
            - Connectionless
            - Indirectly identify through ports
            - [Src port| Dst Port| Length| Chksum| Payload] //32 bits
            - Port is where processes communicate
            - No flow control
            - No guaranteed delivery
            - Demultiplexes messages - gets to the port for the process
    5.2
        - TCP
            - Reliable bytestream (relatively)
            - Connection oriented
            - end-to-end -> flow control, quality control, error correction/detection
            - Limit how much data the sender can transmit
            - CONGESTION CONTROL - tcp throttles itself to prevent network overload
    5.4.2 helpful

## Chapter 6

    6.1.1 Network Model
        - Packet Switched
        - Connectionless flows
            - Maintain some info of the flow of packets
        - Service Model
            - Maintain Quality of Service
        - IPv6 Header
          - addresses are 16 bytes long
          - 16 byte source address
        - The IP Protocol
          - Security
          - Strict source routing
          - Loose source routing
          - Rcord route
          - Timestamp

    6.1.2 Taxonomy
        - Router-Centric vs Host-Centric
            - Address the problem from inside
            - Address the problem from the edges

    6.1.3

    Grasp of congestion control
        - responsible for general idea of the algorithms

    congestion low, increase segment size. high, decrease

    Leaky bucket

    Packet queueing
      Queue you place the packet on?
        routing algorithm
      Which packet goes out next?
        queuing algorithm
        route trees
        shortest remaining time
        round robin
    6.2
      feels like layer 3 again-
    6.1-6.3
    6.4,6.5 recommended
    6.5.2 very strongly recommended
      RSVP - reserve bandwidth

## Chapter 8 - Security

    8.3.4 (Diffie-Helman key exchange)
      establish a secret between people who are speaking in the open
    8.4.1 (PGP)
    secure one way hashes
    public key encryption
    private key encryption
    token exchanges

    authentication protocols
    attacks: why we predistribute keys

## Chapter 9

    DNS
      recursive vs iterative lookups
    9.3.1

## Review Session

    Distance Vector
        - Can have questions
        - Don't trust others about their knowledge of the state of the links
            - Why trust at all? You need to
        - Hops vs costs and their reliability of reporting

    Link State
        - Modification/hypothetical: Tree flooding
            - Has to be explained well enough
            - But could be done
        - Be familiar in the sense of
            - Flooding
                - Share information to the entire network
                - Prevent it from being detrimental
                    - Sequences - Routing layer -> recognize repeats
                    - Avoid cycles - MAC
            - Minimum spanning tree
                - Cost of transmitting
        - Content addressable hypothetical
            - Lookups for tables -> could speed up the process
            - Does the algorithm have to run fast?
            - Routers do many tasks
                - Routing, updating routing tables, scheduling packet sends
            - Scheduling needs to run as fast as possible
            - Don't let packets get dropped!
        - Packet scheduling
            - Shortest completion time first
                - Get credit for arrival time

    Congestion Control
        - Assured forwading -> carpool lane
            - send out the VIP first -> like having a higher priority
            - Allows you to have one set of traffic unaffected by load caused by another
        - Expedited forwarding
        - Assured vs Expedited
            - "Top priority go thruogh first, second go second" -> priority scheme
            - "This class goes first, the filthy peasants wait"
        - TCP/IP don't have priority metadata
            - Need to label packets
        - MPLS - routers agree to pack extra metadata
            - Standard for adding labeling to network layer packets
        - LAYERS
        - Data streams/channels have different performance requirements
        - Average rate -> doesn't necessarily help with quality
            - Thumb drive a week
            - Look more for minimum
        - Specify quality with:
            - Token rate - average data rate
                - enough to support the service
            - Token data cap - peak burst
                - max the network/recipient can take
            - Leaky bucket size - leaky bucket, max amnt of data sent
                - Don't send if there are no tokens
            - peak, largest, average
                - Helps for building buffer. Get at this average rate, no more than that rate

    Quality of Service
        - Token bucket rate
        - Token bucket cap
        - Leaky bucket size
        - What they mean, how they apply

    Congestion
        - Super bad thing
        - Congested builds congestions
        - Avoid or Prevent? Yes. It depends. Both.
        - Can you deal with congestion at the source?
            - To an extent
            - Router = can't, but tell the people ahead of you to slow down
            - End-to-end, causing yourself to have your packets lost
        - TCP
            - responds by tring to reduce the transmission rate
            - If everybody is using, everybody will back off
            - Uses unreliable protocol to send packets reliably
                - Packets timing out is packets not getting through
                - Wait for acknowledgement
                - When do you react to/identify a loss?
        - Not complete solutions that fix for everybody
            - Routing won't have all the information
            - Transport layer has no understanding of route, not sources

    Layer 4
        - End to end delivery, slightly more complicated header
            - Deliver to the port
        - Also congestion control
            - How much more data you can send in the window
            - Throttle the data being sent
            - Wait on sending more data until it's worth it to send more data, it can be received
        - Slow start algorithm
            - Ramp up the speeds, restart from previous known good speed
        - Early detection
        - 6.3,4,5 light reading
        - Datagram
            - Network with path to destination vs independent datagram - dedicated path
                - Which better to sustain?
                - Router can check whenever it wants
            - RSVP
                - Reserve amount of bandwidth
                - On top of IP
            - Don't need to know the specifics, but the concepts
            - IP can give routing information

    Application Layer
        - DNS
        - General idea
        - http uses DNS
        - How to build session layer
            - Basic crypto stuff
            - done on case by case
        - Detect retransmissions/loss
            - Timestamp
            - Sequence numbers
                - How many in a sequence
                    - Somehow say not done yet
                    - Wait until message says done
                    - Need to guarantee integrity
                    - Flag - more coming/done

    Crypto
        - Secure one way hash
            - NOT A CHECKSUM
        - Public key encryption
        - Private key encryption

    Security
        - Challenge-response key exchange
            - Prove yourself, prove them
        - Diffie-helman key exchange
        - Practice Qs
            - Do you need to start with a shared secret?
                - No
            - Completely unbreakable
                - No such thing
