import plotly 

plotly.tools.set_credentials_file(username='margaretwm3', api_key='o4uSEA2nAwBDp7Q7jBxK')
import plotly.plotly as py
import plotly.graph_objs as go

# Create random data with numpy
import numpy as np

fileSize = ['256MB', '512MB','1GB','2GB','3GB','4GB','5GB']
time = [0.001496,0.001451,0.001341,0.001290,0.007099,0.009104,0.009337]


# Create a trace
trace1 = go.Scatter(
    x = fileSize,
    y = time,
    name = "Avg. read I/O time",
    line = dict(
        width = 4
    )
)

# trace2 = go.Scatter(
#     y = graph_test_acc,
#     name = "Testing Accuracy"
# )

data = [trace1]

layout = go.Layout(
    title='File Sizes vs. Avg read per-block I/O Time',
    xaxis=dict(
        title='File Sizes',
        titlefont=dict(
            family='Courier New, monospace',
            size=18,
            color='#7f7f7f'
        )
    ),
    yaxis=dict(
        title='Avg. read per-block I/O Time in ms',
        titlefont=dict(
            family='Courier New, monospace',
            size=18,
            color='#7f7f7f'
        )
    )
)
fig = go.Figure(data=data, layout=layout)

py.iplot(fig, filename='File Size vs. Avg read per-block Time')