struct Version {
    bit<8> major;
    bit<8> minor;
}

error {
    NoError,
    PacketTooShort,
    NoMatch,
    EmptyStack,
    FullStack,
    OverwritingHeader
}

extern packet_in {
    void extract<T>(out T hdr);
    void extract<T>(out T variableSizeHeader, in bit<32> sizeInBits);
    T lookahead<T>();
    void advance(in bit<32> sizeInBits);
    bit<32> length();
}

extern packet_out {
    void emit<T>(in T hdr);
}

match_kind {
    exact,
    ternary,
    lpm
}

match_kind {
    range,
    selector
}

struct standard_metadata_t {
    bit<9>  ingress_port;
    bit<9>  egress_spec;
    bit<9>  egress_port;
    bit<32> clone_spec;
    bit<32> instance_type;
    bit<1>  drop;
    bit<16> recirculate_port;
    bit<32> packet_length;
}

extern Checksum16 {
    bit<16> get<D>(in D data);
}

enum CounterType {
    Packets,
    Bytes,
    Both
}

extern Counter {
    Counter(bit<32> size, CounterType type);
    void increment(in bit<32> index);
}

extern DirectCounter {
    DirectCounter(CounterType type);
}

extern Meter {
    Meter(bit<32> size, CounterType type);
    void meter<T>(in bit<32> index, out T result);
}

extern DirectMeter<T> {
    DirectMeter(CounterType type);
    void read(out T result);
}

extern Register<T> {
    Register(bit<32> size);
    void read(out T result, in bit<32> index);
    void write(in bit<32> index, in T value);
}

extern ActionProfile {
    ActionProfile(bit<32> size);
}

enum HashAlgorithm {
    crc32,
    crc16,
    random,
    identity
}

extern ActionSelector {
    ActionSelector(HashAlgorithm algorithm, bit<32> size, bit<32> outputWidth);
}

parser Parser<H, M>(packet_in b, out H parsedHdr, inout M meta, inout standard_metadata_t standard_metadata);
control VerifyChecksum<H, M>(in H hdr, inout M meta, inout standard_metadata_t standard_metadata);
control Ingress<H, M>(inout H hdr, inout M meta, inout standard_metadata_t standard_metadata);
control Egress<H, M>(inout H hdr, inout M meta, inout standard_metadata_t standard_metadata);
control ComputeCkecksum<H, M>(inout H hdr, inout M meta);
control Deparser<H>(packet_out b, in H hdr);
package V1Switch<H, M>(Parser<H, M> p, VerifyChecksum<H, M> vr, Ingress<H, M> ig, Egress<H, M> eg, ComputeCkecksum<H, M> ck, Deparser<H> dep);
header data_t {
    bit<32> f1;
    bit<32> f2;
    bit<16> h1;
    bit<8>  b1;
    bit<8>  b2;
}

header extra_t {
    bit<16> h;
    bit<8>  b1;
    bit<8>  b2;
}

struct metadata {
}

struct headers {
    @name("data") 
    data_t     data;
    @name("extra") 
    extra_t[4] extra;
}

parser ParserImpl(packet_in packet, out headers hdr, inout metadata meta, inout standard_metadata_t standard_metadata) {
    @name("extra") state extra {
        packet.extract(hdr.extra.next);
        transition select(hdr.extra.last.b2) {
            8w0x80 &&& 8w0x80: extra;
            default: accept;
        }
    }
    @name("start") state start {
        packet.extract(hdr.data);
        transition extra;
    }
}

control ingress(inout headers hdr, inout metadata meta, inout standard_metadata_t standard_metadata) {
    action NoAction_0() {
    }
    action NoAction_1() {
    }
    action NoAction_2() {
    }
    action NoAction_3() {
    }
    action NoAction_4() {
    }
    @name("set0b1") action set0b1_0(bit<8> val) {
        hdr.extra[0].b1 = val;
    }
    @name("act1") action act1_0(bit<8> val) {
        hdr.extra[0].b1 = val;
    }
    @name("act2") action act2_0(bit<8> val) {
        hdr.extra[0].b1 = val;
    }
    @name("act3") action act3_0(bit<8> val) {
        hdr.extra[0].b1 = val;
    }
    @name("noop") action noop_0() {
    }
    @name("noop") action noop() {
    }
    @name("noop") action noop_1() {
    }
    @name("noop") action noop_2() {
    }
    @name("noop") action noop_3() {
    }
    @name("setb2") action setb2_0(bit<8> val) {
        hdr.data.b2 = val;
    }
    @name("set1b1") action set1b1_0(bit<8> val) {
        hdr.extra[1].b1 = val;
    }
    @name("set2b2") action set2b2_0(bit<8> val) {
        hdr.extra[2].b2 = val;
    }
    @name("setb1") action setb1_0(bit<9> port, bit<8> val) {
        hdr.data.b1 = val;
        standard_metadata.egress_spec = port;
    }
    @name("ex1") table ex1_0() {
        actions = {
            set0b1_0;
            act1_0;
            act2_0;
            act3_0;
            noop_0;
            NoAction_0;
        }
        key = {
            hdr.extra[0].h: ternary;
        }
        default_action = NoAction_0();
    }
    @name("tbl1") table tbl1_0() {
        actions = {
            setb2_0;
            noop;
            NoAction_1;
        }
        key = {
            hdr.data.f2: ternary;
        }
        default_action = NoAction_0();
    }
    @name("tbl2") table tbl2_0() {
        actions = {
            set1b1_0;
            noop_1;
            NoAction_2;
        }
        key = {
            hdr.data.f2: ternary;
        }
        default_action = NoAction_0();
    }
    @name("tbl3") table tbl3_0() {
        actions = {
            set2b2_0;
            noop_2;
            NoAction_3;
        }
        key = {
            hdr.data.f2: ternary;
        }
        default_action = NoAction_0();
    }
    @name("test1") table test1_0() {
        actions = {
            setb1_0;
            noop_3;
            NoAction_4;
        }
        key = {
            hdr.data.f1: ternary;
        }
        default_action = NoAction_0();
    }
    apply {
        test1_0.apply();
        switch (ex1_0.apply().action_run) {
            act1_0: {
                tbl1_0.apply();
            }
            act2_0: {
                tbl2_0.apply();
            }
            act3_0: {
                tbl3_0.apply();
            }
        }

    }
}

control egress(inout headers hdr, inout metadata meta, inout standard_metadata_t standard_metadata) {
    apply {
    }
}

control DeparserImpl(packet_out packet, in headers hdr) {
    apply {
        packet.emit(hdr.data);
        packet.emit(hdr.extra);
    }
}

control verifyChecksum(in headers hdr, inout metadata meta, inout standard_metadata_t standard_metadata) {
    apply {
    }
}

control computeChecksum(inout headers hdr, inout metadata meta) {
    apply {
    }
}

V1Switch(ParserImpl(), verifyChecksum(), ingress(), egress(), computeChecksum(), DeparserImpl()) main;