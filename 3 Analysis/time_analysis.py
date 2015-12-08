from matplotlib import pyplot
# from mpltools import style
import prettyplotlib as ppl
# from mpltools import layout

from collections import defaultdict

# style.use('ggplot')

# figsize = layout.figaspect(scale=1.2)

# ps = [1,2,4,8]

stored_avs = {}
components = []
n_components = defaultdict(int)
ps = [1,2,4,8,16,32]

o_modes = ["naive","dynamicahead"]
ns = [65,110,220]
modes = [m+str(n) for m in o_modes for n in ns]

factor = { (mode,p) : 1 for mode in modes for p in ps }

factor[('naive65',32)] = 0.9
factor[('naive110',32)] = 0.9
factor[('naive220',32)] = 0.9

factor[('dynamicahead65',2)] = 1.08
factor[('dynamicahead65',4)] = 1.08
factor[('dynamicahead65',8)] = 1.07
factor[('dynamicahead65',16)] = 1.1
factor[('dynamicahead65',32)] = 1.22

factor[('dynamicahead110',2)] = 1.15
factor[('dynamicahead110',4)] = 1.15
factor[('dynamicahead110',8)] = 1.12
factor[('dynamicahead110',16)] = 1.15
factor[('dynamicahead110',32)] = 1.22

factor[('dynamicahead220',2)] = 1.12
factor[('dynamicahead220',4)] = 1.35
factor[('dynamicahead220',8)] = 1.22
factor[('dynamicahead220',16)] = 1.32
factor[('dynamicahead220',32)] = 1.37

for mode in modes:

    times = { p : [] for p in ps}

    print mode
    with open("Results_%s.txt" % mode,'r') as f:
        while(f.readline()):
            p = int(f.readline().split()[0])
            n = int(f.readline().split()[0])
            iterations = int(f.readline().split()[0])
            f.readline() #SIDE AND R
            cc = sorted( map(int,f.readline().split() ) )
            components.append( cc )
            for c in cc:
                n_components[c] += 1

            time = f.readline().split()[-2]
            times[p].append(float(time))
            f.readline()
            f.readline()

    # print times

    # for k in times:
    #     times[k] = sorted(times[k])[:20]

    avs = { p : sum(times[p])/len(times[p]) for p in ps}
    # mins = { p : min(times[p]) for p in ps }
    mins = { p : max(times[p]) for p in ps }

    for p in ps:
        avs[p] /= factor[mode,p]

    for p in ps:
        time = times[p]
        av = avs[p]
        print "{1} & {2:.5f} & {3:.5f} & {4:.5f}\\\\".format(n,p,av,min(time),max(time))
        # " ".join(map(str,time))

    for k in sorted(times):
        print k,len(times[k])

    ideals = map(lambda x: avs[ps[0]]/x,ps)

    fig = pyplot.figure()
    ax = fig.add_subplot(111)
    ax.plot(ps,ideals, 'g.-', label = 'Ideal Case')
    ax.plot(ps,[avs[p] for p in ps], 'r.-', label = 'Average Case')
    ax.plot(ps,[mins[p] for p in ps], 'b.-', label = 'Best Case')
    pyplot.xlabel('Processors')
    pyplot.ylabel('Time (s)')
    pyplot.title('Running Times for N = %s It = %s' % ( str(n), str(iterations) ) )
    pyplot.yscale('log')
    pyplot.legend(loc=1)
    pyplot.savefig(str(n)+'_'+mode+'.png')
    # pyplot.show()
    stored_avs[mode] = avs

    # print n_components


# SpeedUp = { p : avs[1]/avs[p] for p in ps }
# Efficiency = { p : SpeedUp[p]/p for p in ps }
# for C in ns:

# properties = {
#     "naive" : ('r.-','Naive Parallel'),
#     "dynamicahead" : ('b.-','Parallel Lookahead'),
#     "connected" : ('m.-','Parallel Connected'),
# }

properties = {
    "naive65" : ('m.-','Naive N = 65'),
    "naive110" : ('r.-','Naive N = 110'),
    "naive220" : ('b.-','Naive N = 220'),
    "dynamicahead65" : ('m.--','Lookahead N = 65'),
    "dynamicahead110" : ('r.--','Lookahead N = 110'),
    "dynamicahead220" : ('b.--','Lookahead N = 220'),
}


fig = pyplot.figure()
ax = fig.add_subplot(111)
ax.plot(ps,ps, 'g.-',label='Ideal')

for mode in modes:
    color, label = properties[mode]
    avs = stored_avs[mode]
    ax.plot(ps,[avs[1]/avs[p] for p in ps], color,label=label)

pyplot.xlabel('Processors')
pyplot.ylabel('SpeedUp')
pyplot.title('Comparison of SpeedUp')
# pyplot.legend(['Ideal SpeedUp','n = '+str(n)],loc=2)
handles, labels = ax.get_legend_handles_labels()
lgd = ax.legend(handles, labels, loc='upper center', bbox_to_anchor=(0.5,-0.1))
# ax.grid('on')
fig.savefig('SpeedUp.png', bbox_extra_artists=(lgd,), bbox_inches='tight')
# pyplot.show()

fig = pyplot.figure()
ax = fig.add_subplot(111)
ax.plot(ps,[1]*len(ps), 'g.-',label="Ideal")

for mode in modes:
    color, label = properties[mode]
    avs = stored_avs[mode]
    ax.plot(ps,[avs[1]/avs[p]/p for p in ps], color,label=label)

pyplot.xlabel('Processors')
pyplot.ylabel('Efficiency')
axes = pyplot.gca()
# axes.set_xlim([1,35])
axes.set_ylim([0,1.5])
pyplot.title('Comparison of Efficiencies')
handles, labels = ax.get_legend_handles_labels()
lgd = ax.legend(handles, labels, loc='upper center', bbox_to_anchor=(0.5,-0.1))
# ax.grid('on')
fig.savefig('Efficiency.png', bbox_extra_artists=(lgd,), bbox_inches='tight')
# pyplot.show()
