from matplotlib import pyplot
# from mpltools import style
import prettyplotlib as ppl
# from mpltools import layout
from collections import defaultdict
# style.use('ggplot')

# figsize = layout.figaspect(scale=1.2)

ps = [1,2,4,8,16,32]

# symbols_explored = { p : [] for p in ps}

n = 15
components = []
n_components = defaultdict(int)
o_modes = ["naive","dynamicahead"]
ns = [110]
modes = [m+str(n) for m in o_modes for n in ns]

for mode in modes:
    times = { p : [] for p in ps}

    systems = { p : [] for p in ps}
    symbols = { p : [] for p in ps}

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
            f.readline()
            c,np = [],[]
            for i in range(p):
                values = map(int,f.readline().split())
                c.append(values[1])
                np.append(values[2])
            systems[p].append(c)
            symbols[p].append(np)
            time = f.readline().split()[-2]
            times[p].append(float(time))
            f.readline()
            f.readline()

    # print times

    # for k in times:
    #     times[k] = sorted(times[k])[:20]

    avs = { p : sum(times[p])/len(times[p]) for p in ps}
    mins = { p : min(times[p]) for p in ps }
    # for p in ps:
    #     time = times[p]
    #     av = avs[p]
    #     print "{1} & {2:.5f} & {3:.5f} & {4:.5f}\\\\".format(n,p,av,min(time),max(time))
    #     # " ".join(map(str,time))

    symbols_per_thread = {}
    total_symbols = {}
    ideal_symbols_per_thread = {}
    max_symbols_per_thread = {}
    min_symbols_per_thread = {}

    for proc in ps:
        x = [sum(p) for p in symbols[proc]]
        total_symbols[proc] = sum(x)/len(x)
        y = [sum(p)*1.0/len(p) for p in symbols[proc]]
        symbols_per_thread[proc] = sum(y)/len(y)
        z = total_symbols[proc]*1.0/proc
        ideal_symbols_per_thread[proc] = z
        u = [max(p) for p in symbols[proc]]
        max_symbols_per_thread[proc] = sum(u)/len(u)
        v = [min(p) for p in symbols[proc]]
        min_symbols_per_thread[proc] = sum(v)/len(v)
        print "{0} &  {1:09.1f} & {2:09.1f} & {3:7d}\\\\".format(proc, symbols_per_thread[proc], ideal_symbols_per_thread[proc], total_symbols[proc])

    systems_per_thread = {}
    total_systems = {}
    ideal_systems_per_thread = {}
    max_systems_per_thread = {}
    min_systems_per_thread = {}

    for proc in ps:
        x = [sum(p) for p in systems[proc]]
        total_systems[proc] = sum(x)/len(x)
        y = [sum(p)*1.0/len(p) for p in systems[proc]]
        systems_per_thread[proc] = sum(y)/len(y)
        z = total_systems[proc]*1.0/proc
        ideal_systems_per_thread[proc] = z
        u = [max(p) for p in systems[proc]]
        max_systems_per_thread[proc] = sum(u)/len(u)
        v = [min(p) for p in systems[proc]]
        min_systems_per_thread[proc] = sum(v)/len(v)
        print "{0} &  {1:02.1f} & {2:02.1f} & {3:7d}\\\\".format(proc, systems_per_thread[proc], ideal_systems_per_thread[proc], total_systems[proc])


    for k in sorted(times):
        print k,len(times[k])

    ideals = map(lambda x: avs[ps[0]]/x,ps)


    fig = pyplot.figure()
    ax = fig.add_subplot(111)
    ax.plot(ps,[total_symbols[p] for p in ps], 'b.-',label='Total symbols explored')
    ax.plot(ps,[ideal_symbols_per_thread[p] for p in ps], 'g.-',label = 'Ideal Node Balancing')
    ax.plot(ps,[symbols_per_thread[p] for p in ps], 'r.-',label=' Average symbols explored per thread')
    ax.plot(ps,[max_symbols_per_thread[p] for p in ps], 'm.-',label='Maximum symbols explored per thread')
    ax.plot(ps,[min_symbols_per_thread[p] for p in ps], 'c.-',label='Minimum symbols explored per thread')
    pyplot.title('Load balancing of symbols')
    pyplot.xlabel('Processors')
    pyplot.ylabel('Symbols translated')
    pyplot.yscale('log')
    handles, labels = ax.get_legend_handles_labels()
    lgd = ax.legend(handles, labels, loc='upper center', bbox_to_anchor=(0.5,-0.1))
    # ax.grid('on')
    fig.savefig('symbols'+mode+'.png', bbox_extra_artists=(lgd,), bbox_inches='tight')
    # pyplot.show()

    fig = pyplot.figure()
    ax = fig.add_subplot(111)
    ax.plot(ps,[total_systems[p] for p in ps], 'b.-',label='Total systems processed')
    ax.plot(ps,[ideal_systems_per_thread[p] for p in ps], 'g.-',label = 'Ideal systems processed per thread')
    ax.plot(ps,[systems_per_thread[p] for p in ps], 'r.-',label=' Average systems processed per thread')
    ax.plot(ps,[max_systems_per_thread[p] for p in ps], 'm.-',label='Maximum systems processed per thread')
    ax.plot(ps,[min_systems_per_thread[p] for p in ps], 'c.-',label='Minimum systems processed per thread')
    # ax.set_xlim([ps[0]-1,ps[-1]+1])
    # ax.set_ylim([min(min_systems_per_thread.values())-1,max(total_systems.values())+1])
    pyplot.yscale('log')
    pyplot.xlabel('Processors')
    pyplot.ylabel('Number of systems derived')
    pyplot.title('Load balancing of systems')
    handles, labels = ax.get_legend_handles_labels()
    lgd = ax.legend(handles, labels, loc='upper center', bbox_to_anchor=(0.5,-0.1))
    # ax.grid('on')
    fig.savefig('systems'+mode+'.png', bbox_extra_artists=(lgd,), bbox_inches='tight')
    # pyplot.show()
