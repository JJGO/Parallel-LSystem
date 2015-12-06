from matplotlib import pyplot
# from mpltools import style
import prettyplotlib as ppl
# from mpltools import layout

from collections import defaultdict

# style.use('ggplot')

# figsize = layout.figaspect(scale=1.2)

ps = [1,2,4]

stored_avs = {}
components = []
n_components = defaultdict(int)
# paths_explored = { p : [] for p in ps}

modes = ["parallel_naive"]
for mode in modes:
    times = { p : [] for p in ps}

    print mode
    with open("../2 C++/%s.txt" % mode,'r') as f:
        while(f.readline()):
            p = int(f.readline().split()[0])
            n = int(f.readline().split()[0])
            iterations = int(f.readline().split()[0])
            cc = sorted( map(int,f.readline().split() ) )
            components.append( cc )
            for c in cc:
                n_components[c] += 1

            time = f.readline().split()[-2]
            times[p].append(float(time))
            f.readline()
            f.readline()

    # print times

    for k in times:
        times[k] = sorted(times[k])[:10]

    avs = { p : sum(times[p])/len(times[p]) for p in ps}
    mins = { p : min(times[p]) for p in ps }

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

properties = {
    modes[0] : ('r.-','Naive Parallel')
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
