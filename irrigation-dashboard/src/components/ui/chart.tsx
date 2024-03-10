import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, ResponsiveContainer } from 'recharts';

const Chart = ({ x, xAxisKey: y, data, yAxisLabel }: {
    x: string,
    xAxisKey: string,
    yAxisLabel: string,
    data: any
}) => {
    return (
        <ResponsiveContainer width="100%" height={350}>
            <LineChart
                width={300}
                height={300}
                data={data}
            >
                <Line type="monotone" dataKey={x} stroke="#2dac5c" />
                <CartesianGrid stroke='#ccc'></CartesianGrid>
                <XAxis dataKey={y} />
                <YAxis label={{ value: yAxisLabel, angle: -90, position: 'insideLeft' }} />
                <Tooltip />
            </LineChart>
        </ResponsiveContainer>
    );
}

export { Chart }