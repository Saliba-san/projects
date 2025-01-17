(s.boot;)
(s.quit;)

(
  SynthDef.new(\pulseTest, {
    arg ampHz=4, fund=40, maxPartial=4, fnew=4, phase=0.5, width=0.5;
    var amp1, amp2, freq1, freq2, sig1, sig2;
    amp1 = LFPulse.kr(ampHz, 0, 0.12) * 0.75;
    amp2 = LFPulse.kr(ampHz, phase, 0.12) * 0.75;
    freq1 = LFNoise0.kr(fnew).exprange(fund, fund*maxPartial).round(fund);
    freq2 = LFNoise0.kr(fnew).exprange(fund, fund*maxPartial).round(fund);
    freq1 = freq1 * LFPulse.kr(8, add:1);
    freq2 = freq2 * LFPulse.kr(8, add:1);
    sig1 = Pulse.ar(freq1, width, amp1);
    sig2 = Pulse.ar(freq2, width, amp2);
    sig1 = FreeVerb.ar(sig1, 0.7, 0.8, 0.25);
    sig2 = FreeVerb.ar(sig2, 0.7, 0.8, 0.25);
    Out.ar(0, sig1);
    Out.ar(1, sig2);
  }).add;
)


x = Synth.new(\pulseTest);
x.set(\fund, 90);
x.set(\width, 0.1);
x.set(\ampHz, 2);
x.set(\maxPartial, 3);
x.free;

y = Synth.new(\pulseTest);
y.set(\fund, 52);
y.set(\width, 0.1);
y.set(\ampHz, 2.9);
y.set(\maxPartial, 3);
y.free;



