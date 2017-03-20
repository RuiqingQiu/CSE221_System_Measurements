import plotly 

plotly.tools.set_credentials_file(username='margaretwm3', api_key='o4uSEA2nAwBDp7Q7jBxK')
import plotly.plotly as py
import plotly.graph_objs as go

# Create random data with numpy
import numpy as np


fileSize = ['64MB', '128MB','256MB','512MB','1GB']
fileSize_logged = ['6', '7','8','9','10'] # MB - log2(MB)

time = [0.049825,0.054462,0.057123,0.070578,0.079834] # ms
time_logged = [4.697,4.736,4.757,4.849,4.902] # ns log10(ms)


time_rand = [0.163305,0.202365,0.204159,0.203914,0.204189]
time_rand_logged = [5.213,5.306,5.310,5.309,5.310]


# Create a trace
trace1 = go.Scatter(
    x = fileSize_logged,
    y = time_logged,
    name = "Sequential Access",
    line = dict(
        width = 4
    )
)

trace2 = go.Scatter(
    x = fileSize_logged,
    y = time_rand_logged,
    name = "Random Access",
    line=dict(
        width=4
    )
)

data = [trace1,trace2]

layout = go.Layout(
    title='Logged File Sizes vs. Logged Per-Block File Read Time',
    xaxis=dict(
        title='Logged File Sizes in MB (log2(MB))',
        titlefont=dict(
            family='Courier New, monospace',
            size=18,
            color='#7f7f7f'
        )
    ),
    yaxis=dict(
        title='Logged Per-Block File Read Time in ns(log10(ns))',
        titlefont=dict(
            family='Courier New, monospace',
            size=18,
            color='#7f7f7f'
        )
    )
)
fig = go.Figure(data=data, layout=layout)

py.iplot(fig, filename='Logged File Sizes vs. Logged Per-Block File Read Time')
