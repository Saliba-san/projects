(s.boot;)
s.scope;

(
w = Scale.major.degrees;

x = { (w.choose + [42, 48, 60, 72].choose).midicps};

r = {SinOsc.ar(rrand(0.4, 4), rrand(8, 20))};

y = { Pan2.ar(SinOsc.ar(x.value + r.value, mul:0.1) * EnvGen.kr(Env.sine(10), doneAction:2), rrand(-0.8, 0.8))};

t = Task{ 
  100.do{
    7.do{ y.play; };
    7.wait;
  }
};
t.start;
)

//Chromatic Scale from 0 to 11 of C : [C, C#, D, D#, E, F, F#, G, G#, A, A#, B]
