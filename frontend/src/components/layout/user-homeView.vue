<template>
    <div>
        <nav class="navbar navbar-light bg-light">
            <div class="container-fluid">
                <div class="row flex-nowrap">
                    <div class="col-auto">
                        <img src="@/assets/location.png" class="h-14 mr-3" alt="Current Location" width="50px" />
                    </div>
                    <div class="col" style="padding: 0;">
                        <h3 style="color: #37517e;height: 20px;">Current Location</h3>
                        <span style="color: #37517e;"> {{ location.address }}</span>
                    </div>
                </div>
                <form class="d-flex" style="width: 41%;;">
                    <input class="form-control me-4" type="search" placeholder="Enter a location" aria-label="Search">
                    <button class="btn btn-outline-secondary" type="submit">Search</button>
                    <img src="@/assets/message.png" style="width: 36px; margin-left: 15px;">
                </form>
            </div>
        </nav>
        <div class="container-fluid">
            <div class="row flex-nowrap">
                <div class="col-auto">
                    <div class="card mb-3" style="width: 17rem;">
                        <div class="card-body">
                            <h5 class="card-title" style="text-transform: uppercase;">Coordinates</h5>
                            <br>
                            <div class="row g-3 mb-3 align-items-center">
                                <div class="col-auto">
                                    <label class="col-form-label">Latitude</label>
                                </div>
                                <div class="col">
                                    <input class="form-control" type="text" :value="location.Latitude" aria-label="readonly"
                                        readonly>
                                </div>
                            </div>
                            <div class="row g-3 align-items-center">
                                <div class="col-auto">
                                    <label class="col-form-label">Longitude</label>
                                </div>
                                <div class="col">
                                    <input class="form-control" type="text" :value="location.Longitude"
                                        aria-label="readonly" readonly>
                                </div>
                            </div>
                        </div>
                    </div>
                    <div class="card" style="width: 17rem;">
                        <div class="card-body">
                            <h5 class="card-title" style="text-transform: uppercase;">Car Conditions</h5>
                            <br>
                            <div class="row g-3 mb-3 align-items-center">
                                <div class="col-auto">
                                    <label class="col-form-label">Speed</label>
                                </div>
                                <div class="col">
                                    <input class="form-control" type="text" value="52.37" aria-label="readonly" readonly>
                                </div>
                                <div class="col-auto">
                                    <span id="passwordHelpInline" class="form-text">
                                        Klm/h
                                    </span>
                                </div>
                            </div>
                            <div class="row g-3 mb-3 align-items-center">
                                <div class="col-auto">
                                    <label class="col-form-label">Max Speed</label>
                                </div>
                                <div class="col">
                                    <input class="form-control" type="number" value="90" aria-label="readonly">
                                </div>
                                <div class="col-auto">
                                    <span id="passwordHelpInline" class="form-text">
                                        Klm/h
                                    </span>
                                </div>
                            </div>
                            <div class="row g-3 mb-3 align-items-center">
                                <div class="form-check form-switch">
                                    <input class="form-check-input" type="checkbox" role="switch"
                                        id="flexSwitchCheckChecked" checked>
                                    <label class="form-check-label" for="flexSwitchCheckChecked">Notifications</label>
                                </div>
                            </div>
                            <div class="alert alert-secondary" role="alert">
                                Receive alerts on the conditions of your car (Max
                                speed exceeded or accident)
                            </div>
                            <br>
                        </div>
                    </div>
                </div>
                <div class="col">
                    <l-map style="height: 585px" :zoom="zoom" :center="center">
                        <l-tile-layer :url="url"></l-tile-layer>
                        <l-marker :lat-lng="markerLatLng"></l-marker>
                    </l-map>
                </div>
            </div>
        </div>
    </div>
</template>
<script>
import { LMap, LTileLayer, LMarker } from "@vue-leaflet/vue-leaflet";
import "leaflet/dist/leaflet.css";
import axios from 'axios'
export default {
    components: {
        LMap,
        LTileLayer,
        LMarker,
    },
    data() {
        return {
            location: {
                address: '',
                Latitude: null,
                Longitude: null,
            },
            url: "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png",
            zoom: 12,
            center: [52.37, 4.9],
            markerLatLng: [52.37, 4.8],

        }
    },
    methods: {
        async fetchPositionFromAPI() {
            try {
                // Make API request to fetch position data
                const data = await axios.get('http://localhost:3000/messages');
                const NewData = data.data;
                // Update the markerLatLng ref with the received position data
                this.markerLatLng = [NewData.Latitude, NewData.Longitude];
                this.center = [NewData.Latitude, NewData.Longitude];
                this.location.Latitude = NewData.Latitude;
                this.location.Longitude = NewData.Longitude;
                this.location.address = NewData.city;
            } catch (error) {
                console.error("Error fetching position data:", error);
            }

        },

    },
    mounted() {
        this.$watch("markerLatLng", (newPosition) => {
            this.$nextTick(() => {
                if (this.$refs.marker) {
                    this.$refs.marker.setLatLng(newPosition);
                }
            });
        });

        // Fetch position data every 1 second
        setInterval(this.fetchPositionFromAPI, 5000);
    }

};
</script>
<style>
.leaflet-container {
    width: 100%;
}
</style>