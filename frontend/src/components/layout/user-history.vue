<template>
    <div>
        <h1 style="text-align: center; color: #37517e; padding-top: 15px;">History</h1>
        <br>
        <table class="table">
            <thead>
                <tr>
                    <th scope="col">#</th>
                    <th scope="col">Date</th>
                    <th scope="col">City</th>
                    <th scope="col">Latitude</th>
                    <th scope="col">Longitude </th>
                </tr>
            </thead>
            <tbody>
                <tr v-for="(item, index) in historyData" :key="item._id">
                    <th scope="row">{{ index + 1 + startIndex }}</th>
                    <td>{{ item.formattedDate }}</td>
                    <td>{{ item.city }}</td>
                    <td>{{ item.Latitude }}</td>
                    <td>{{ item.Longitude }}</td>
                </tr>
            </tbody>
        </table>

    </div>
</template>
<script>
import axios from 'axios'
import moment from 'moment';
export default {
    name: 'HistoryView',
    data() {
        return {
            historyData: [],
            startIndex: 0,
        }
    },
    methods: {
        async fetchHistoryData() {
            try {
                const response = await axios.get('http://localhost:3000/api/history');
                this.historyData = response.data.map(item => ({
                    Latitude: item.Latitude,
                    Longitude: item.Longitude,
                    city: item.city,
                    formattedDate: moment(item.Timestamp).format('YYYY-MM-DD HH:mm:ss')
                }));
            } catch (error) {
                console.error(error);
            }
        },
        incrementindextab() {
            return ++this.indextab;
        }
    },
    created() {
        this.fetchHistoryData();
    }

}
</script>