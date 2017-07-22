snd = Input([0, 1])

cfreq = SigTo(440, 0.05, 440)
q = SigTo(5, 0.05, 5)

filter = Reson(snd, freq=cfreq, q=q).out()

out = Mix(filter, voices=2).out()