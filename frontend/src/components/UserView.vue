<template>
    <div>
        <div class="container-fluid">
            <div class="row flex-nowrap">
                <div class="col-auto col-md-3 col-xl-2 px-sm-2 px-0 bg-light">
                    <sidebar @item-clicked="handleSidebarItemClick"></sidebar>
                </div>
                <div class="col" style="padding: 0;">
                    <!-- Render the selected component based on the activeItem -->
                    <component :is="activeItemComponent"></component>

                </div>
            </div>
        </div>
    </div>
</template>
<script>
import Sidebar from './SideBarView.vue';
import Component1 from './layout/user-homeView.vue';
import Component2 from './layout/user-history.vue';
import Component3 from './Component3.vue';
// import Component4 from './Component4.vue';
// import Component5 from './Component5.vue';
export default {
    name: 'UserView',
    components: { Sidebar, Component1, Component2, Component3 },
    data() {
        return {
            activeItemComponent: Component1
        }
    },
    methods: {
        handleSidebarItemClick(item) {
            // Set the selected component based on the clicked sidebar item
            switch (item) {
                case 1:
                    this.activeItemComponent = Component1;
                    break;
                case 2:
                    this.activeItemComponent = Component2;
                    break;
                case 3:
                    this.activeItemComponent = Component3;
                    break;
                default:
                    this.activeItemComponent = null;
            }
        }
    }

};




</script>
<style >
.nav-link {
    color: #000000;
}
</style>