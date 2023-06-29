<template>
    <div>
        <div class="d-flex flex-column align-items-center align-items-sm-start px-3 pt-2 text-white min-vh-100">

            <ul class="nav nav-pills flex-column mb-sm-auto mb-0 align-items-center align-items-sm-start" id="menu">
                <li class="nav-item" @click="handleItemClick(1)">
                    <a href="#" class="nav-link align-middle px-0">
                        <i class="fs-4 bi-house"></i> <span class="ms-1 d-none d-sm-inline">Home</span>
                    </a>
                </li>
                <li @click="handleItemClick(2)">
                    <a href="#" class="nav-link px-0 align-middle">
                        <i class="fs-4 bi-clock-history"></i> <span class="ms-1 d-none d-sm-inline">History</span></a>
                </li>
                <li @click="handleItemClick(3)">
                    <a class="nav-link px-0 align-middle ">
                        <i class="fs-4 bi-bell"></i> <span class="ms-1 d-none d-sm-inline">Notifications</span></a>
                </li>
                <li @click="handleItemClick(4)">
                    <a class="nav-link px-0 align-middle">
                        <i class="fs-4 bi-gear"></i> <span class="ms-1 d-none d-sm-inline">Settings</span> </a>
                </li>
                <li @click="handleItemClick(5)">
                    <a href="#" class="nav-link px-0 align-middle">
                        <i class="fs-4 bi-person-circle"></i> <span class="ms-1 d-none d-sm-inline">Profile</span>
                    </a>
                </li>
            </ul>
            <hr>
            <div class="dropdown">
                <a href="#" class="d-flex align-items-center text-white text-decoration-none dropdown-toggle"
                    id="dropdownUser1" data-bs-toggle="dropdown" aria-expanded="false">
                    <img src="https://github.com/mdo.png" alt="hugenerd" width="30" height="30" class="rounded-circle">
                    <span class="d-none d-sm-inline mx-1">loser</span>
                </a>
                <ul class="dropdown-menu dropdown-menu-dark text-small shadow" aria-labelledby="dropdownUser1">
                    <li><a class="dropdown-item" href="#">New project...</a></li>
                    <li><a class="dropdown-item" href="#">Settings</a></li>
                    <li><a class="dropdown-item" href="#">Profile</a></li>
                    <li>
                        <hr class="dropdown-divider">
                    </li>
                    <li><a class="dropdown-item" href="#">Sign out</a></li>
                </ul>
            </div>
        </div>
    </div>
</template>
<script>
export default {
    data() {
        return {


        };
    },
    methods: {
        handleItemClick(pagename) {
            // Emit an event or perform any other logic when an item is clicked
            this.$emit('item-clicked', pagename);
        }
    }
};
</script>