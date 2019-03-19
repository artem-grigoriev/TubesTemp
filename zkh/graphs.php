<html>
<head><title>Make Chart</title></head>
<body>
<canvas id="myChart"></canvas>
<script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.4.0/Chart.min.js"></script>
<script>
    var ctx = document.getElementById('myChart').getContext('2d');
    var chart = new Chart(ctx, {
        // The type of chart we want to create
        type: 'line',

        // The data for our datasets
        data: {
            labels: ["January", "February", "March", "April", "May", "June", "July"],
            datasets: [{
                label: "My First dataset",
                backgroundColor: 'rgb(255, 255, 255)',
                borderColor: 'rgb(255, 99, 132)',
                fill: false
                data: [0, 10, 5, 2, 20, 30, 45],
                yAxisID: 'y-axis-1',
            },
                {
                label: "My Sec dataset",
                backgroundColor: 'rgb(255, 255, 255)',
                borderColor: 'rgb(255, 255, 132)',
                fill: false,
                data: [5, 10, 2, 5, 20, 20, 10],
                yAxisID: 'y-axis-2',
            }]
        };


        // Configuration options go here
        options: {}
    });
</script>
</body>
</html>